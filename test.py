import sys
import os
import unittest
from datetime import date

root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, root)

import cal

TODAY = date.today()


class TestParseDate(unittest.TestCase):
	def test_dd(self):
		tpl = cal.parse_date('13')
		self.assertEqual(tpl, {
			'day': 13,
			'year': TODAY.year,
		})

	def test_dd_star(self):
		tpl = cal.parse_date('13*')
		self.assertEqual(tpl, {
			'day': 13,
		})

	def test_mmdd(self):
		tpl = cal.parse_date('02/13')
		self.assertEqual(tpl, {
			'day': 13,
			'month': 2,
			'year': TODAY.year,
		})

	def test_mmdd_star(self):
		tpl = cal.parse_date('02/13*')
		self.assertEqual(tpl, {
			'day': 13,
			'month': 2,
		})

	def test_yyyymmdd(self):
		tpl = cal.parse_date('1999/02/13')
		self.assertEqual(tpl, {
			'day': 13,
			'month': 2,
			'year': 1999,
		})

	def test_yyyymmdd_star(self):
		tpl = cal.parse_date('1999/02/13*')
		self.assertEqual(tpl, {
			'day': 13,
			'month': 2,
		})

	def test_yyyymmdd_repeat(self):
		tpl = cal.parse_date('1999/02/13+2')
		self.assertEqual(tpl, {
			'day': 13,
			'month': 2,
			'year': 1999,
			'repeat': 2,
		})

	def test_weekday(self):
		tpl = cal.parse_date('Sat')
		self.assertEqual(tpl, {
			'weekday': 5,
		})

	def test_weekday_with_nth_of_month(self):
		tpl = cal.parse_date('Sat-1')
		self.assertEqual(tpl, {
			'weekday': 5,
			'nth_of_month': -1,
		})

	def test_mm_weekday(self):
		tpl = cal.parse_date('02/Sat+2')
		self.assertEqual(tpl, {
			'month': 2,
			'weekday': 5,
			'nth_of_month': 2,
		})

	def test_yyyymm_weekday(self):
		tpl = cal.parse_date('1999/02/Sat+2')
		self.assertEqual(tpl, {
			'month': 2,
			'year': 1999,
			'weekday': 5,
			'nth_of_month': 2,
		})

	def test_easter(self):
		tpl = cal.parse_date('Easter')
		self.assertEqual(tpl, {
			'from_easter': 0,
		})

	def test_easter_with_offset(self):
		tpl = cal.parse_date('Easter+30')
		self.assertEqual(tpl, {
			'from_easter': 30,
		})


class TestIsMatch(unittest.TestCase):
	def test_dd(self):
		tpl = {
			'day': 13,
		}
		self.assertTrue(cal.is_match(tpl, date(1999, 2, 13)))
		self.assertFalse(cal.is_match(tpl, date(1999, 2, 14)))

	def test_mmdd(self):
		tpl = {
			'day': 13,
			'month': 2,
		}
		self.assertTrue(cal.is_match(tpl, date(1999, 2, 13)))
		self.assertFalse(cal.is_match(tpl, date(1999, 2, 14)))
		self.assertFalse(cal.is_match(tpl, date(1999, 3, 13)))

	def test_yyyymmdd(self):
		tpl = {
			'day': 13,
			'month': 2,
			'year': 1999,
		}
		self.assertTrue(cal.is_match(tpl, date(1999, 2, 13)))
		self.assertFalse(cal.is_match(tpl, date(1999, 2, 14)))
		self.assertFalse(cal.is_match(tpl, date(1999, 3, 13)))
		self.assertFalse(cal.is_match(tpl, date(2000, 2, 13)))

	def test_yyyymmdd_repeat(self):
		tpl = {
			'day': 13,
			'month': 2,
			'year': 1999,
			'repeat': 2,
		}
		self.assertTrue(cal.is_match(tpl, date(1999, 2, 13)))
		self.assertTrue(cal.is_match(tpl, date(1999, 2, 27)))
		self.assertFalse(cal.is_match(tpl, date(1999, 2, 14)))
		self.assertFalse(cal.is_match(tpl, date(1999, 2, 20)))

	def test_weekday(self):
		tpl = {
			'weekday': 5,
		}
		self.assertTrue(cal.is_match(tpl, date(1999, 2, 13)))
		self.assertFalse(cal.is_match(tpl, date(1999, 2, 14)))

	def test_weekday_with_nth_of_month(self):
		tpl = {
			'weekday': 5,
			'nth_of_month': 2,
		}
		self.assertTrue(cal.is_match(tpl, date(1999, 2, 13)))
		self.assertFalse(cal.is_match(tpl, date(1999, 2, 14)))
		self.assertFalse(cal.is_match(tpl, date(1999, 2, 20)))

	def test_mm_weekday(self):
		tpl = {
			'month': 2,
			'weekday': 5,
			'nth_of_month': 2,
		}
		self.assertTrue(cal.is_match(tpl, date(1999, 2, 13)))
		self.assertFalse(cal.is_match(tpl, date(1999, 2, 14)))
		self.assertFalse(cal.is_match(tpl, date(1999, 2, 20)))
		self.assertFalse(cal.is_match(tpl, date(1999, 3, 13)))

	def test_yyyymm_weekday(self):
		tpl = {
			'month': 2,
			'year': 1999,
			'weekday': 5,
			'nth_of_month': 2,
		}
		self.assertTrue(cal.is_match(tpl, date(1999, 2, 13)))
		self.assertFalse(cal.is_match(tpl, date(1999, 2, 14)))
		self.assertFalse(cal.is_match(tpl, date(1999, 2, 20)))
		self.assertFalse(cal.is_match(tpl, date(1999, 3, 13)))
		self.assertFalse(cal.is_match(tpl, date(2000, 2, 12)))

	def test_easter(self):
		tpl = {
			'from_easter': 0,
		}
		self.assertTrue(cal.is_match(tpl, date(2000, 4, 23)))
		self.assertFalse(cal.is_match(tpl, date(2000, 4, 25)))

	def test_easter_with_offset(self):
		tpl = {
			'from_easter': 2,
		}
		self.assertTrue(cal.is_match(tpl, date(2000, 4, 25)))
		self.assertFalse(cal.is_match(tpl, date(2000, 4, 23)))
