#!/usr/bin/env python
"""BSD calendar reimplementation

The calendar utility reads events from plain text files and outputs today's
events. The files look something like this::

    #include <holiday>
    #include <birthday>

    06/15\tJune 15
    Thu\tEvery Thursday.
    15\t15th of every month.

    05/Sun+2\tsecond Sunday in May (Muttertag)
    04/Sun-1\tlast Sunday in April

    Easter-2\tGood Friday (2 days before Easter)
    Paskha\tOrthodox Easter

This implementation adds some new features while dropping others, most notably,
the date formats are not completely compatible::

    # added formats
    1999/06/15\tJune 15 1999
    1999/06/15*\tJune 15 (usefull for birthdays)
    1999/05/Sun+2\tsecond Sunday in May 1999
    1999/06/15+2\tJune 15 1999 and every second week since then

    # removed formats (mostly alternative formats)
    Jun. 15\t06/15
    15 June\t06/15
    Thursday\tThu
    June\t06/01
    15 *\t15

    May Sun+2\t05/Sun+2
    04/SunLast\t04/Sun-1
"""

import os
import re
import argparse
import subprocess
import datetime

__version__ = '0.0.0'

TODAY = datetime.date.today()


def easter(year, paskha=False):
	# https://de.wikipedia.org/wiki/Gau%C3%9Fsche_Osterformel#Eine_erg.C3.A4nzte_Osterformel
	k = int(year / 100)
	if paskha:
		s = 0
		m = 15
	else:
		s = 2 - int((3 * k + 3) / 4)
		m = 17 - s - int((8 * k + 13) / 25)
	a = year % 19
	d = (19 * a + m) % 30
	r = int((d + int(a / 11)) / 29)
	og = 21 + d - r
	sz = 7 - (year + int(year / 4) + s) % 7
	oe = 7 - (og - sz) % 7
	os = og + oe

	if paskha:
		os += k - int(year / 400) - 2

	return datetime.date(year, 3, 1) + datetime.timedelta(os - 1)


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

	if 'from_paskha' in tpl:
		d = date - datetime.timedelta(tpl['from_paskha'])
		if easter(d.year, paskha=True) != d:
			return False

	return True


def parse_weekday(s):
	_d = datetime.datetime.strptime(s + ' 01', '%a %U')
	return _d.weekday()


def parse_date(s):
	m = re.match('^(.*)([+-]\d+)$', s)
	if m:
		s = m.groups()[0]
		n = int(m.groups()[1] or 0)
	else:
		n = None

	# easter
	if s == 'Easter':
		return {'from_easter': n or 0}

	if s == 'Paskha':
		return {'from_paskha': n or 0}

	# date
	try:
		a = s.rstrip('*')
		_d = datetime.datetime.strptime(a, '%d')
		tpl = {'day': _d.day}
		if not s.endswith('*'):
			tpl['year'] = TODAY.year
		return tpl
	except ValueError:
		pass

	try:
		a = s.rstrip('*')
		_d = datetime.datetime.strptime(a, '%m/%d')
		tpl = {'day': _d.day, 'month': _d.month}
		if not s.endswith('*'):
			tpl['year'] = TODAY.year
		return tpl
	except ValueError:
		pass

	try:
		a = s.rstrip('*')
		_d = datetime.datetime.strptime(a, '%Y/%m/%d')
		tpl = {'day': _d.day, 'month': _d.month}
		if not s.endswith('*'):
			tpl['year'] = _d.year
		if n is not None:
			tpl['repeat'] = n
		return tpl
	except ValueError:
		pass

	# weekday
	try:
		tpl = {'weekday': parse_weekday(s)}
		if n is not None:
			tpl['nth_of_month'] = n
		return tpl
	except ValueError:
		pass

	try:
		d, w = s.rsplit('/', 1)
		_d = datetime.datetime.strptime(d, '%m')
		tpl = {'month': _d.month, 'weekday': parse_weekday(w)}
		if n is not None:
			tpl['nth_of_month'] = n
		return tpl
	except ValueError:
		pass

	try:
		d, w = s.rsplit('/', 1)
		_d = datetime.datetime.strptime(d, '%Y/%m')
		tpl = {'month': _d.month, 'year': _d.year, 'weekday': parse_weekday(w)}
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
	parser = argparse.ArgumentParser(description=__doc__.split('\n')[0])
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

	replace = {}

	if args.today:
		replace['day'] = int(args.today[-2:])

		if len(args.today) >= 4:
			replace['month'] = int(args.today[-4:-2])
		if len(args.today) == 8:
			replace['year'] = int(args.today[-8:-4])

	args.d_today = TODAY.replace(**replace)
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
				star = '' if 'year' in tpl else '*'
				print(date.strftime('%b %d') + star + '\t' + desc)
		date = date + datetime.timedelta(1)


if __name__ == '__main__':
	main()
