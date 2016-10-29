import sys
import os
import unittest
from datetime import date

root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, root)

import cal

TODAY = date.today()


class TestEaster(unittest.TestCase):
	def test_easter(self):
		self.assertEqual(cal.easter(2000), date(2000, 4, 23))
		self.assertEqual(cal.easter(2001), date(2001, 4, 15))
		self.assertEqual(cal.easter(2002), date(2002, 3, 31))
		self.assertEqual(cal.easter(2003), date(2003, 4, 20))
		self.assertEqual(cal.easter(2004), date(2004, 4, 11))
		self.assertEqual(cal.easter(2005), date(2005, 3, 27))
		self.assertEqual(cal.easter(2006), date(2006, 4, 16))
		self.assertEqual(cal.easter(2007), date(2007, 4, 8))
		self.assertEqual(cal.easter(2008), date(2008, 3, 23))
		self.assertEqual(cal.easter(2009), date(2009, 4, 12))
		self.assertEqual(cal.easter(2010), date(2010, 4, 4))
		self.assertEqual(cal.easter(2011), date(2011, 4, 24))
		self.assertEqual(cal.easter(2012), date(2012, 4, 8))
		self.assertEqual(cal.easter(2013), date(2013, 3, 31))
		self.assertEqual(cal.easter(2014), date(2014, 4, 20))
		self.assertEqual(cal.easter(2015), date(2015, 4, 5))
		self.assertEqual(cal.easter(2016), date(2016, 3, 27))
		self.assertEqual(cal.easter(2017), date(2017, 4, 16))
		self.assertEqual(cal.easter(2018), date(2018, 4, 1))
		self.assertEqual(cal.easter(2019), date(2019, 4, 21))
		self.assertEqual(cal.easter(2020), date(2020, 4, 12))
		self.assertEqual(cal.easter(2021), date(2021, 4, 4))
		self.assertEqual(cal.easter(2022), date(2022, 4, 17))
		self.assertEqual(cal.easter(2023), date(2023, 4, 9))
		self.assertEqual(cal.easter(2024), date(2024, 3, 31))
		self.assertEqual(cal.easter(2025), date(2025, 4, 20))
		self.assertEqual(cal.easter(2026), date(2026, 4, 5))
		self.assertEqual(cal.easter(2027), date(2027, 3, 28))
		self.assertEqual(cal.easter(2028), date(2028, 4, 16))
		self.assertEqual(cal.easter(2029), date(2029, 4, 1))
		self.assertEqual(cal.easter(2030), date(2030, 4, 21))


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
