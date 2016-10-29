"""asd"""

import os
import re
import argparse
import subprocess
import datetime

__version__ = '0.0.0'


def is_leap(year):
	if year % 4 != 0:
		return False
	elif year % 100 != 0:
		return True
	elif year % 400 != 0:
		return False
	else:
		return True


def easter(year):
	"""From debian bsdmainutils."""
	# silly, but it works
	e_a = year % 19
	e_b = int(year / 100)
	e_c = year % 100

	e_d = int(e_b / 4)
	e_e = e_b % 4
	e_f = int((e_b + 8) / 25)
	e_g = int((e_b + 1 - e_f) / 3)
	e_h = ((19 * e_a) + 15 + e_b - (e_d + e_g)) % 30
	e_i = int(e_c / 4)
	e_k = e_c % 4
	e_l = (32 + 2 * e_e + 2 * e_i - (e_h + e_k)) % 7
	e_m = int((e_a + 11 * e_h + 22 * e_l) / 451)
	e_n = int((e_h + e_l + 114 - (7 * e_m)) / 31)
	e_p = (e_h + e_l + 114 - (7 * e_m)) % 31
	e_p = e_p + 1

	e_q = 31 + 28 + e_p
	if is_leap(year):
		e_q += 1

	if e_n == 4:
		e_q += 31

	return datetime.date(year, 1, 1) + datetime.timedelta(e_q - 1)


def is_match(tpl, date):
	if 'repeat' in tpl:
		if 'day' in tpl and 'month' in tpl and 'year' in tpl:
			reference = datetime.date(tpl['year'], tpl['month'], tpl['day'])
			delta = date - reference
			if delta.days % (7 * tpl['repeat']) != 0:
				return False
		else:
			raise ValueError('repeat used without day, month and year')
	else:
		if 'day' in tpl and date.day != tpl['day']:
			return False
		if 'month' in tpl and date.month != tpl['month']:
			return False
		if 'year' in tpl and date.year != tpl['year']:
			return False

	if 'weekday' in tpl and date.weekday() != tpl['weekday']:
		return False

	if 'nth_of_month' in tpl:
		a = tpl['nth_of_month']
		outside = date - datetime.timedelta(a * 7)
		if outside.month == date.month:
			return False
		b = a + 1 if a < 0 else a - 1
		inside = date - datetime.timedelta(b * 7)
		if inside.month != date.month:
			return False

	if 'from_easter' in tpl:
		d = date - datetime.timedelta(tpl['from_easter'])
		if easter(d.year) != d:
			return False

	return True


def parse_weekday(s):
	_d = datetime.datetime.strptime(s + ' 01', '%a %U')
	return _d.weekday()


def parse_date(s):
	s = s.strip(' *')

	m = re.match('^(.*)([+-]\d+)$', s)
	if m:
		s = m.groups()[0]
		n = int(m.groups()[1] or 0)
	else:
		n = None

	# Easter
	if s == 'Easter':
		return {'from_easter': n or 0}

	# date
	try:
		_d = datetime.datetime.strptime(s, '%d')
		return {'day': _d.day}
	except ValueError:
		pass

	try:
		_d = datetime.datetime.strptime(s, '%m/%d')
		return {'day': _d.day, 'month': _d.month}
	except ValueError:
		pass

	try:
		_d = datetime.datetime.strptime(s, '%Y/%m/%d')
		tpl = {'day': _d.day, 'month': _d.month, 'year': _d.year}
		if n is not None:
			tpl['repeat'] = n
		return tpl
	except ValueError:
		pass

	# Weekday
	try:
		tpl = {'weekday': parse_weekday(s)}
		if n is not None:
			tpl['nth_of_month'] = n
		return tpl
	except ValueError:
		pass

	raise ValueError('Invalid date template: %s', s)


def parse_line(line):
	s_date, desc = line.split('\t', 1)
	return parse_date(s_date), desc


def get_calendar(path):
	abspath = os.path.abspath(path)
	paths = [
		os.path.dirname(abspath),
		os.path.expanduser('~/.calendar'),
		'/etc/calendar',
		'/usr/share/calendar',
	]
	cmd = ['cpp', '-P', '-traditional'] + ['-I' + p for p in paths] + [abspath]
	return subprocess.check_output(cmd).decode('utf8')


def get_entries(path):
	lines = get_calendar(path).split('\n')
	return [parse_line(l) for l in lines if l]


def _parse_args(argv=None):
	parser = argparse.ArgumentParser(description=__doc__)
	parser.add_argument('--version', '-V', action='version', version=__version__)
	parser.add_argument('-A', type=int, dest='days_after', default=1, nargs='?',
		help='Print lines from today and next num days (forward, future).')
	parser.add_argument('-B', type=int, dest='days_before', default=0, nargs='?',
		help='Print lines from today and previous num days (backward, past).')
	parser.add_argument('-f', nargs='?', dest='file', metavar='calendarfile',
		default=os.path.expanduser('~/.calendar/calendar'))
	parser.add_argument('-t', nargs='?', dest='today', metavar='[[yyyy.mm.dd',
		help='Act like the specified value is "today" instead of using the '
		'current date.')
	return parser.parse_args(argv)


def parse_args(argv=None):
	args = _parse_args(argv)

	today = datetime.date.today()
	replace = {}

	if args.today:
		replace['day'] = int(args.today[-2:])

		if len(args.today) >= 4:
			replace['month'] = int(args.today[-4:-2])
		if len(args.today) == 8:
			replace['year'] = int(args.today[-8:-4])

	args.d_today = today.replace(**replace)
	args.d_start = args.d_today - datetime.timedelta(args.days_before)
	args.d_end = args.d_today + datetime.timedelta(args.days_after)

	return args


def main():
	args = parse_args()
	entries = get_entries(args.file)

	date = args.d_start
	while date <= args.d_end:
		for tpl, desc in entries:
			if is_match(tpl, date):
				print(date.strftime('%b %d') + '\t' + desc)
		date = date + datetime.timedelta(1)


if __name__ == '__main__':
	main()
