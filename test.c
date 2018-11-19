#define test
#include "calendar.c"

#define run_test(test) do { char *message = test(); tests_run++; if (message) { tests_failed++; printf("Failed: %s\n", message); } } while (0)

int tests_run = 0;
int tests_failed = 0;

static char *test_easter() {
	if (!date_comp(easter(2000, false), mkdate(2000, 4, 23))) return "easter 2000";
	if (!date_comp(easter(2001, false), mkdate(2001, 4, 15))) return "easter 2001";
	if (!date_comp(easter(2002, false), mkdate(2002, 3, 31))) return "easter 2002";
	if (!date_comp(easter(2003, false), mkdate(2003, 4, 20))) return "easter 2003";
	if (!date_comp(easter(2004, false), mkdate(2004, 4, 11))) return "easter 2004";
	if (!date_comp(easter(2005, false), mkdate(2005, 3, 27))) return "easter 2005";
	if (!date_comp(easter(2006, false), mkdate(2006, 4, 16))) return "easter 2006";
	if (!date_comp(easter(2007, false), mkdate(2007, 4,  8))) return "easter 2007";
	if (!date_comp(easter(2008, false), mkdate(2008, 3, 23))) return "easter 2008";
	if (!date_comp(easter(2009, false), mkdate(2009, 4, 12))) return "easter 2009";
	if (!date_comp(easter(2010, false), mkdate(2010, 4,  4))) return "easter 2010";
	if (!date_comp(easter(2011, false), mkdate(2011, 4, 24))) return "easter 2011";
	if (!date_comp(easter(2012, false), mkdate(2012, 4,  8))) return "easter 2012";
	if (!date_comp(easter(2013, false), mkdate(2013, 3, 31))) return "easter 2013";
	if (!date_comp(easter(2014, false), mkdate(2014, 4, 20))) return "easter 2014";
	if (!date_comp(easter(2015, false), mkdate(2015, 4,  5))) return "easter 2015";
	if (!date_comp(easter(2016, false), mkdate(2016, 3, 27))) return "easter 2016";
	if (!date_comp(easter(2017, false), mkdate(2017, 4, 16))) return "easter 2017";
	if (!date_comp(easter(2018, false), mkdate(2018, 4,  1))) return "easter 2018";
	if (!date_comp(easter(2019, false), mkdate(2019, 4, 21))) return "easter 2019";
	if (!date_comp(easter(2020, false), mkdate(2020, 4, 12))) return "easter 2020";
	if (!date_comp(easter(2021, false), mkdate(2021, 4,  4))) return "easter 2021";
	if (!date_comp(easter(2022, false), mkdate(2022, 4, 17))) return "easter 2022";
	if (!date_comp(easter(2023, false), mkdate(2023, 4,  9))) return "easter 2023";
	if (!date_comp(easter(2024, false), mkdate(2024, 3, 31))) return "easter 2024";
	if (!date_comp(easter(2025, false), mkdate(2025, 4, 20))) return "easter 2025";
	if (!date_comp(easter(2026, false), mkdate(2026, 4,  5))) return "easter 2026";
	if (!date_comp(easter(2027, false), mkdate(2027, 3, 28))) return "easter 2027";
	if (!date_comp(easter(2028, false), mkdate(2028, 4, 16))) return "easter 2028";
	if (!date_comp(easter(2029, false), mkdate(2029, 4,  1))) return "easter 2029";
	if (!date_comp(easter(2030, false), mkdate(2030, 4, 21))) return "easter 2030";
	return 0;
}

static char *test_paskha() {
	if (!date_comp(easter(2000, true), mkdate(2000, 4, 30))) return "paskha 2000";
	if (!date_comp(easter(2001, true), mkdate(2001, 4, 15))) return "paskha 2001";
	if (!date_comp(easter(2002, true), mkdate(2002, 5,  5))) return "paskha 2002";
	if (!date_comp(easter(2003, true), mkdate(2003, 4, 27))) return "paskha 2003";
	if (!date_comp(easter(2004, true), mkdate(2004, 4, 11))) return "paskha 2004";
	if (!date_comp(easter(2005, true), mkdate(2005, 5,  1))) return "paskha 2005";
	if (!date_comp(easter(2006, true), mkdate(2006, 4, 23))) return "paskha 2006";
	if (!date_comp(easter(2007, true), mkdate(2007, 4,  8))) return "paskha 2007";
	if (!date_comp(easter(2008, true), mkdate(2008, 4, 27))) return "paskha 2008";
	if (!date_comp(easter(2009, true), mkdate(2009, 4, 19))) return "paskha 2009";
	if (!date_comp(easter(2010, true), mkdate(2010, 4,  4))) return "paskha 2010";
	if (!date_comp(easter(2011, true), mkdate(2011, 4, 24))) return "paskha 2011";
	if (!date_comp(easter(2012, true), mkdate(2012, 4, 15))) return "paskha 2012";
	if (!date_comp(easter(2013, true), mkdate(2013, 5,  5))) return "paskha 2013";
	if (!date_comp(easter(2014, true), mkdate(2014, 4, 20))) return "paskha 2014";
	if (!date_comp(easter(2015, true), mkdate(2015, 4, 12))) return "paskha 2015";
	if (!date_comp(easter(2016, true), mkdate(2016, 5,  1))) return "paskha 2016";
	if (!date_comp(easter(2017, true), mkdate(2017, 4, 16))) return "paskha 2017";
	if (!date_comp(easter(2018, true), mkdate(2018, 4,  8))) return "paskha 2018";
	if (!date_comp(easter(2019, true), mkdate(2019, 4, 28))) return "paskha 2019";
	if (!date_comp(easter(2020, true), mkdate(2020, 4, 19))) return "paskha 2020";
	if (!date_comp(easter(2021, true), mkdate(2021, 5,  2))) return "paskha 2021";
	if (!date_comp(easter(2022, true), mkdate(2022, 4, 24))) return "paskha 2022";
	if (!date_comp(easter(2023, true), mkdate(2023, 4, 16))) return "paskha 2023";
	if (!date_comp(easter(2024, true), mkdate(2024, 5,  5))) return "paskha 2024";
	if (!date_comp(easter(2025, true), mkdate(2025, 4, 20))) return "paskha 2025";
	if (!date_comp(easter(2026, true), mkdate(2026, 4, 12))) return "paskha 2026";
	if (!date_comp(easter(2027, true), mkdate(2027, 5,  2))) return "paskha 2027";
	if (!date_comp(easter(2028, true), mkdate(2028, 4, 16))) return "paskha 2028";
	if (!date_comp(easter(2029, true), mkdate(2029, 4,  8))) return "paskha 2029";
	if (!date_comp(easter(2030, true), mkdate(2030, 4, 28))) return "paskha 2030";
	return 0;
}

bool tpl_comp(struct tpl a, struct tpl b) {
	return \
		a.year == b.year && \
		a.month == b.month && \
		a.day == b.day && \
		a.repeat == b.repeat && \
		a.weekday == b.weekday && \
		a.nth_of_month == b.nth_of_month && \
		a.from_easter == b.from_easter && \
		a.from_paskha == b.from_paskha;
}

struct tpl parse_date_mut(const char *s) {
	char *_s = malloc(strlen(s));
	strcpy(_s, s);
	struct tpl tpl = parse_date(_s);
	free(_s);
	return tpl;
}

char *test_parse_date_dd() {
	struct tpl actual = parse_date_mut("13");
	struct tpl expected = mktpl();
	expected.year = today()->tm_year + 1900;
	expected.day = 13;

	if (!tpl_comp(actual, expected)) return "parse_date_mut(\"13\")";
	return 0;
}

char *test_parse_date_dd_star() {
	struct tpl actual = parse_date_mut("13*");
	struct tpl expected = mktpl();
	expected.day = 13;

	if (!tpl_comp(actual, expected)) return "parse_date_mut(\"13*\")";
	return 0;
}

char *test_parse_date_mmdd() {
	struct tpl actual = parse_date_mut("02/13");
	struct tpl expected = mktpl();
	expected.year = today()->tm_year + 1900 + (today()->tm_mon + 1 > 2 ? 1 : 0);
	expected.month = 2;
	expected.day = 13;

	if (!tpl_comp(actual, expected)) return "parse_date_mut(\"02/13\")";
	return 0;
}

char *test_parse_date_mmdd_star() {
	struct tpl actual = parse_date_mut("02/13*");
	struct tpl expected = mktpl();
	expected.month = 2;
	expected.day = 13;

	if (!tpl_comp(actual, expected)) return "parse_date_mut(\"02/13*\")";
	return 0;
}

char *test_parse_date_yyyymmdd() {
	struct tpl actual = parse_date_mut("1999/02/13");
	struct tpl expected = mktpl();
	expected.year = 1999;
	expected.month = 2;
	expected.day = 13;

	if (!tpl_comp(actual, expected)) return "parse_date_mut(\"1999/02/13\")";
	return 0;
}

char *test_parse_date_yyyymmdd_star() {
	struct tpl actual = parse_date_mut("1999/02/13*");
	struct tpl expected = mktpl();
	expected.month = 2;
	expected.day = 13;

	if (!tpl_comp(actual, expected)) return "parse_date_mut(\"1999/02/13*\")";
	return 0;
}

char *test_parse_date_yyyymmdd_repeat() {
	struct tpl actual = parse_date_mut("1999/02/13+2");
	struct tpl expected = mktpl();
	expected.year = 1999;
	expected.month = 2;
	expected.day = 13;
	expected.repeat = 2;

	if (!tpl_comp(actual, expected)) return "parse_date_mut(\"1999/02/13+2\")";
	return 0;
}

char *test_parse_date_weekday() {
	struct tpl actual = parse_date_mut("Sat");
	struct tpl expected = mktpl();
	expected.weekday = 7;

	if (!tpl_comp(actual, expected)) return "parse_date_mut(\"Sat\")";
	return 0;
}

char *test_parse_date_weekday_with_nth_of_month() {
	struct tpl actual = parse_date_mut("Sat-1");
	struct tpl expected = mktpl();
	expected.weekday = 7;
	expected.nth_of_month = -1;

	if (!tpl_comp(actual, expected)) return "parse_date_mut(\"Sat-1\")";
	return 0;
}

char *test_parse_date_mm_weekday() {
	struct tpl actual = parse_date_mut("02/Sat+2");
	struct tpl expected = mktpl();
	expected.month = 2;
	expected.weekday = 7;
	expected.nth_of_month = 2;

	if (!tpl_comp(actual, expected)) return "parse_date_mut(\"02/Sat+2\")";
	return 0;
}

char *test_parse_date_yyyymm_weekday() {
	struct tpl actual = parse_date_mut("1999/02/Sat+2");
	struct tpl expected = mktpl();
	expected.year = 1999;
	expected.month = 2;
	expected.weekday = 7;
	expected.nth_of_month = 2;

	if (!tpl_comp(actual, expected)) return "parse_date_mut(\"1999/02/Sat+2\")";
	return 0;
}

char *test_parse_date_easter() {
	struct tpl actual = parse_date_mut("Easter");
	struct tpl expected = mktpl();
	expected.from_easter = 0;

	if (!tpl_comp(actual, expected)) return "parse_date_mut(\"Easter\")";
	return 0;
}

char *test_parse_date_easter_with_offset() {
	struct tpl actual = parse_date_mut("Easter+30");
	struct tpl expected = mktpl();
	expected.from_easter = 30;

	if (!tpl_comp(actual, expected)) return "parse_date_mut(\"Easter+30\")";
	return 0;
}

char *test_is_match_dd() {
	struct tpl tpl = mktpl();
	tpl.day = 13;

	if (!is_match(tpl, mkdate(1999, 2, 13))) return "is_match dd";
	if (is_match(tpl, mkdate(1999, 2, 14))) return "!is_match dd";
	return 0;
}

char *test_is_match_mmdd() {
	struct tpl tpl = mktpl();
	tpl.month = 2;
	tpl.day = 13;

	if (!is_match(tpl, mkdate(1999, 2, 13))) return "is_match mmdd";
	if (is_match(tpl, mkdate(1999, 2, 14))) return "!is_match mmdd";
	if (is_match(tpl, mkdate(1999, 3, 13))) return "!is_match mmdd";
	return 0;
}

char *test_is_match_yyyymmdd() {
	struct tpl tpl = mktpl();
	tpl.year = 1999;
	tpl.month = 2;
	tpl.day = 13;

	if (!is_match(tpl, mkdate(1999, 2, 13))) return "is_match yyyymmdd";
	if (is_match(tpl, mkdate(1999, 2, 14))) return "!is_match yyyymmdd";
	if (is_match(tpl, mkdate(1999, 3, 13))) return "!is_match yyyymmdd";
	if (is_match(tpl, mkdate(2000, 2, 13))) return "!is_match yyyymmdd";
	return 0;
}

char *test_is_match_yyyymmdd_repeat() {
	struct tpl tpl = mktpl();
	tpl.year = 1999;
	tpl.month = 2;
	tpl.day = 13;
	tpl.repeat = 2;

	if (!is_match(tpl, mkdate(1999, 2, 13))) return "is_match yyyymmdd repeat";
	if (!is_match(tpl, mkdate(1999, 2, 27))) return "is_match yyyymmdd repeat";
	if (is_match(tpl, mkdate(1999, 2, 14))) return "!is_match yyyymmdd repeat";
	if (is_match(tpl, mkdate(1999, 2, 20))) return "!is_match yyyymmdd repeat";
	return 0;
}

char *test_is_match_weekday() {
	struct tpl tpl = mktpl();
	tpl.weekday = 7;

	if (!is_match(tpl, mkdate(1999, 2, 13))) return "is_match weekday";
	if (is_match(tpl, mkdate(1999, 2, 14))) return "!is_match weekday";
	return 0;
}

char *test_is_match_weekday_with_nth_of_month() {
	struct tpl tpl = mktpl();
	tpl.weekday = 7;
	tpl.nth_of_month = 2;

	if (!is_match(tpl, mkdate(1999, 2, 13))) return "is_match weekday with nth_of_month";
	if (is_match(tpl, mkdate(1999, 2, 14))) return "!is_match weekday with nth_of_month";
	if (is_match(tpl, mkdate(1999, 2, 20))) return "!is_match weekday with nth_of_month";
	return 0;
}

char *test_is_match_mm_weekday() {
	struct tpl tpl = mktpl();
	tpl.month = 2;
	tpl.weekday = 7;
	tpl.nth_of_month = 2;

	if (!is_match(tpl, mkdate(1999, 2, 13))) return "is_match mm weekday";
	if (is_match(tpl, mkdate(1999, 2, 14))) return "!is_match mm weekday";
	if (is_match(tpl, mkdate(1999, 2, 20))) return "!is_match mm weekday";
	if (is_match(tpl, mkdate(1999, 3, 13))) return "!is_match mm weekday";
	return 0;
}

char *test_is_match_yyyymm_weekday() {
	struct tpl tpl = mktpl();
	tpl.year = 1999;
	tpl.month = 2;
	tpl.weekday = 7;
	tpl.nth_of_month = 2;

	if (!is_match(tpl, mkdate(1999, 2, 13))) return "is_match yyyymm weekday";
	if (is_match(tpl, mkdate(1999, 2, 14))) return "!is_match yyyymm weekday";
	if (is_match(tpl, mkdate(1999, 2, 20))) return "!is_match yyyymm weekday";
	if (is_match(tpl, mkdate(1999, 3, 13))) return "!is_match yyyymm weekday";
	if (is_match(tpl, mkdate(2000, 2, 12))) return "!is_match yyyymm weekday";
	return 0;
}

char *test_is_match_easter() {
	struct tpl tpl = mktpl();
	tpl.from_easter = 0;
	tpl.easter = true;

	if (!is_match(tpl, mkdate(2000, 4, 23))) return "is_match easter";
	if (is_match(tpl, mkdate(2000, 4, 25))) return "!is_match easter";
	return 0;
}

char *test_is_match_easter_with_offset() {
	struct tpl tpl = mktpl();
	tpl.from_easter = 2;
	tpl.easter = true;

	if (!is_match(tpl, mkdate(2000, 4, 25))) return "is_match easter+2";
	if (is_match(tpl, mkdate(2000, 4, 23))) return "!is_match easter+2";
	return 0;
}

char *test_is_match_paskha() {
	struct tpl tpl = mktpl();
	tpl.from_paskha = 0;
	tpl.paskha = true;

	if (!is_match(tpl, mkdate(2000, 4, 30))) return "is_match paskha";
	if (is_match(tpl, mkdate(2000, 4, 28))) return "!is_match paskha";
	return 0;
}

char *test_is_match_paskha_with_offset() {
	struct tpl tpl = mktpl();
	tpl.from_paskha = -2;
	tpl.paskha = true;

	if (!is_match(tpl, mkdate(2000, 4, 28))) return "is_match paskha-2";
	if (is_match(tpl, mkdate(2000, 4, 30))) return "!is_match paskha-2";
	return 0;
}

int main(int argc, char **argv) {
	run_test(test_easter);
	run_test(test_paskha);

	run_test(test_parse_date_dd);
	run_test(test_parse_date_dd_star);
	run_test(test_parse_date_mmdd);
	run_test(test_parse_date_mmdd_star);
	run_test(test_parse_date_yyyymmdd);
	run_test(test_parse_date_yyyymmdd_star);
	run_test(test_parse_date_yyyymmdd_repeat);
	run_test(test_parse_date_weekday);
	run_test(test_parse_date_weekday_with_nth_of_month);
	run_test(test_parse_date_mm_weekday);
	run_test(test_parse_date_yyyymm_weekday);
	run_test(test_parse_date_easter);
	run_test(test_parse_date_easter_with_offset);

	run_test(test_is_match_dd);
	run_test(test_is_match_mmdd);
	run_test(test_is_match_yyyymmdd);
	run_test(test_is_match_yyyymmdd_repeat);
	run_test(test_is_match_weekday);
	run_test(test_is_match_weekday_with_nth_of_month);
	run_test(test_is_match_mm_weekday);
	run_test(test_is_match_yyyymm_weekday);
	run_test(test_is_match_easter);
	run_test(test_is_match_easter_with_offset);
	run_test(test_is_match_paskha);
	run_test(test_is_match_paskha_with_offset);

	printf("Tests run: %d\n", tests_run);
	if (tests_failed) {
		return EXIT_FAILURE;
	}
}
