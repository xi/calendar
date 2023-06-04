#define test
#include "calendar.c"

#define mu_unit(msg) do { printf("%s\n", msg); } while (0)
#define mu_test(msg, fn) do { printf("  %s\n", msg); char *result = fn(); tests_run++; if (result) { tests_failed++; printf("    X %s\n", result); } } while (0)
#define mu_assert(msg, test) do { if (!(test)) return msg; } while (0)

int tests_run = 0;
int tests_failed = 0;

static char *test_easter(void) {
	mu_assert("2000", date_comp(easter(2000, false), mkdate(2000, 4, 23)));
	mu_assert("2001", date_comp(easter(2001, false), mkdate(2001, 4, 15)));
	mu_assert("2002", date_comp(easter(2002, false), mkdate(2002, 3, 31)));
	mu_assert("2003", date_comp(easter(2003, false), mkdate(2003, 4, 20)));
	mu_assert("2004", date_comp(easter(2004, false), mkdate(2004, 4, 11)));
	mu_assert("2005", date_comp(easter(2005, false), mkdate(2005, 3, 27)));
	mu_assert("2006", date_comp(easter(2006, false), mkdate(2006, 4, 16)));
	mu_assert("2007", date_comp(easter(2007, false), mkdate(2007, 4,  8)));
	mu_assert("2008", date_comp(easter(2008, false), mkdate(2008, 3, 23)));
	mu_assert("2009", date_comp(easter(2009, false), mkdate(2009, 4, 12)));
	mu_assert("2010", date_comp(easter(2010, false), mkdate(2010, 4,  4)));
	mu_assert("2011", date_comp(easter(2011, false), mkdate(2011, 4, 24)));
	mu_assert("2012", date_comp(easter(2012, false), mkdate(2012, 4,  8)));
	mu_assert("2013", date_comp(easter(2013, false), mkdate(2013, 3, 31)));
	mu_assert("2014", date_comp(easter(2014, false), mkdate(2014, 4, 20)));
	mu_assert("2015", date_comp(easter(2015, false), mkdate(2015, 4,  5)));
	mu_assert("2016", date_comp(easter(2016, false), mkdate(2016, 3, 27)));
	mu_assert("2017", date_comp(easter(2017, false), mkdate(2017, 4, 16)));
	mu_assert("2018", date_comp(easter(2018, false), mkdate(2018, 4,  1)));
	mu_assert("2019", date_comp(easter(2019, false), mkdate(2019, 4, 21)));
	mu_assert("2020", date_comp(easter(2020, false), mkdate(2020, 4, 12)));
	mu_assert("2021", date_comp(easter(2021, false), mkdate(2021, 4,  4)));
	mu_assert("2022", date_comp(easter(2022, false), mkdate(2022, 4, 17)));
	mu_assert("2023", date_comp(easter(2023, false), mkdate(2023, 4,  9)));
	mu_assert("2024", date_comp(easter(2024, false), mkdate(2024, 3, 31)));
	mu_assert("2025", date_comp(easter(2025, false), mkdate(2025, 4, 20)));
	mu_assert("2026", date_comp(easter(2026, false), mkdate(2026, 4,  5)));
	mu_assert("2027", date_comp(easter(2027, false), mkdate(2027, 3, 28)));
	mu_assert("2028", date_comp(easter(2028, false), mkdate(2028, 4, 16)));
	mu_assert("2029", date_comp(easter(2029, false), mkdate(2029, 4,  1)));
	mu_assert("2030", date_comp(easter(2030, false), mkdate(2030, 4, 21)));
	return 0;
}

static char *test_paskha(void) {
	mu_assert("2000", date_comp(easter(2000, true), mkdate(2000, 4, 30)));
	mu_assert("2001", date_comp(easter(2001, true), mkdate(2001, 4, 15)));
	mu_assert("2002", date_comp(easter(2002, true), mkdate(2002, 5,  5)));
	mu_assert("2003", date_comp(easter(2003, true), mkdate(2003, 4, 27)));
	mu_assert("2004", date_comp(easter(2004, true), mkdate(2004, 4, 11)));
	mu_assert("2005", date_comp(easter(2005, true), mkdate(2005, 5,  1)));
	mu_assert("2006", date_comp(easter(2006, true), mkdate(2006, 4, 23)));
	mu_assert("2007", date_comp(easter(2007, true), mkdate(2007, 4,  8)));
	mu_assert("2008", date_comp(easter(2008, true), mkdate(2008, 4, 27)));
	mu_assert("2009", date_comp(easter(2009, true), mkdate(2009, 4, 19)));
	mu_assert("2010", date_comp(easter(2010, true), mkdate(2010, 4,  4)));
	mu_assert("2011", date_comp(easter(2011, true), mkdate(2011, 4, 24)));
	mu_assert("2012", date_comp(easter(2012, true), mkdate(2012, 4, 15)));
	mu_assert("2013", date_comp(easter(2013, true), mkdate(2013, 5,  5)));
	mu_assert("2014", date_comp(easter(2014, true), mkdate(2014, 4, 20)));
	mu_assert("2015", date_comp(easter(2015, true), mkdate(2015, 4, 12)));
	mu_assert("2016", date_comp(easter(2016, true), mkdate(2016, 5,  1)));
	mu_assert("2017", date_comp(easter(2017, true), mkdate(2017, 4, 16)));
	mu_assert("2018", date_comp(easter(2018, true), mkdate(2018, 4,  8)));
	mu_assert("2019", date_comp(easter(2019, true), mkdate(2019, 4, 28)));
	mu_assert("2020", date_comp(easter(2020, true), mkdate(2020, 4, 19)));
	mu_assert("2021", date_comp(easter(2021, true), mkdate(2021, 5,  2)));
	mu_assert("2022", date_comp(easter(2022, true), mkdate(2022, 4, 24)));
	mu_assert("2023", date_comp(easter(2023, true), mkdate(2023, 4, 16)));
	mu_assert("2024", date_comp(easter(2024, true), mkdate(2024, 5,  5)));
	mu_assert("2025", date_comp(easter(2025, true), mkdate(2025, 4, 20)));
	mu_assert("2026", date_comp(easter(2026, true), mkdate(2026, 4, 12)));
	mu_assert("2027", date_comp(easter(2027, true), mkdate(2027, 5,  2)));
	mu_assert("2028", date_comp(easter(2028, true), mkdate(2028, 4, 16)));
	mu_assert("2029", date_comp(easter(2029, true), mkdate(2029, 4,  8)));
	mu_assert("2030", date_comp(easter(2030, true), mkdate(2030, 4, 28)));
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
	char *_s = malloc(strlen(s) + 1);
	strcpy(_s, s);
	struct tpl tpl = parse_date(_s);
	free(_s);
	return tpl;
}

char *test_parse_date_dd(void) {
	struct tpl actual = parse_date_mut("13");
	struct tpl expected = mktpl();
	expected.year = today()->tm_year + 1900;
	expected.day = 13;

	mu_assert("13", tpl_comp(actual, expected));
	return 0;
}

char *test_parse_date_dd_star(void) {
	struct tpl actual = parse_date_mut("13*");
	struct tpl expected = mktpl();
	expected.day = 13;

	mu_assert("13*)", tpl_comp(actual, expected));
	return 0;
}

char *test_parse_date_mmdd(void) {
	struct tpl actual = parse_date_mut("02/13");
	struct tpl expected = mktpl();
	expected.year = today()->tm_year + 1900 + (today()->tm_mon + 1 > 2 ? 1 : 0);
	expected.month = 2;
	expected.day = 13;

	mu_assert("02/13", tpl_comp(actual, expected));
	return 0;
}

char *test_parse_date_mmdd_star(void) {
	struct tpl actual = parse_date_mut("02/13*");
	struct tpl expected = mktpl();
	expected.month = 2;
	expected.day = 13;

	mu_assert("02/13", tpl_comp(actual, expected));
	return 0;
}

char *test_parse_date_yyyymmdd(void) {
	struct tpl actual = parse_date_mut("1999/02/13");
	struct tpl expected = mktpl();
	expected.year = 1999;
	expected.month = 2;
	expected.day = 13;

	mu_assert("1999/02/13", tpl_comp(actual, expected));
	return 0;
}

char *test_parse_date_yyyymmdd_star(void) {
	struct tpl actual = parse_date_mut("1999/02/13*");
	struct tpl expected = mktpl();
	expected.month = 2;
	expected.day = 13;

	mu_assert("1999/02/13*", tpl_comp(actual, expected));
	return 0;
}

char *test_parse_date_yyyymmdd_repeat(void) {
	struct tpl actual = parse_date_mut("1999/02/13+2");
	struct tpl expected = mktpl();
	expected.year = 1999;
	expected.month = 2;
	expected.day = 13;
	expected.repeat = 2;

	mu_assert("1999/02/13+2", tpl_comp(actual, expected));
	return 0;
}

char *test_parse_date_weekday(void) {
	struct tpl actual = parse_date_mut("Sat");
	struct tpl expected = mktpl();
	expected.weekday = 7;

	mu_assert("Sat", tpl_comp(actual, expected));
	return 0;
}

char *test_parse_date_weekday_with_nth_of_month(void) {
	struct tpl actual = parse_date_mut("Sat+1");
	struct tpl expected = mktpl();
	expected.weekday = 7;
	expected.nth_of_month = 1;

	mu_assert("Sat+1", tpl_comp(actual, expected));
	return 0;
}

char *test_parse_date_weekday_with_nth_last_of_month(void) {
	struct tpl actual = parse_date_mut("Sat-1");
	struct tpl expected = mktpl();
	expected.weekday = 7;
	expected.nth_of_month = -1;

	mu_assert("Sat-1", tpl_comp(actual, expected));
	return 0;
}

char *test_parse_date_mm_weekday(void) {
	struct tpl actual = parse_date_mut("02/Sat+2");
	struct tpl expected = mktpl();
	expected.month = 2;
	expected.weekday = 7;
	expected.nth_of_month = 2;

	mu_assert("02/Sat+2", tpl_comp(actual, expected));
	return 0;
}

char *test_parse_date_yyyymm_weekday(void) {
	struct tpl actual = parse_date_mut("1999/02/Sat+2");
	struct tpl expected = mktpl();
	expected.year = 1999;
	expected.month = 2;
	expected.weekday = 7;
	expected.nth_of_month = 2;

	mu_assert("1999/02/Sat+2", tpl_comp(actual, expected));
	return 0;
}

char *test_parse_date_easter(void) {
	struct tpl actual = parse_date_mut("Easter");
	struct tpl expected = mktpl();
	expected.from_easter = 0;

	mu_assert("Easter", tpl_comp(actual, expected));
	return 0;
}

char *test_parse_date_easter_with_offset(void) {
	struct tpl actual = parse_date_mut("Easter+30");
	struct tpl expected = mktpl();
	expected.from_easter = 30;

	mu_assert("Easter+30", tpl_comp(actual, expected));
	return 0;
}

char *test_is_match_dd(void) {
	struct tpl tpl = mktpl();
	tpl.day = 13;

	mu_assert("date does match", is_match(tpl, mkdate(1999, 2, 13)));
	mu_assert("next day does not match", !is_match(tpl, mkdate(1999, 2, 14)));
	return 0;
}

char *test_is_match_mmdd(void) {
	struct tpl tpl = mktpl();
	tpl.month = 2;
	tpl.day = 13;

	mu_assert("date does match", is_match(tpl, mkdate(1999, 2, 13)));
	mu_assert("next day does not match", !is_match(tpl, mkdate(1999, 2, 14)));
	mu_assert("next month does not match", !is_match(tpl, mkdate(1999, 3, 13)));
	return 0;
}

char *test_is_match_yyyymmdd(void) {
	struct tpl tpl = mktpl();
	tpl.year = 1999;
	tpl.month = 2;
	tpl.day = 13;

	mu_assert("date does match", is_match(tpl, mkdate(1999, 2, 13)));
	mu_assert("next day does not match", !is_match(tpl, mkdate(1999, 2, 14)));
	mu_assert("next month does not match", !is_match(tpl, mkdate(1999, 3, 13)));
	mu_assert("next year does not match", !is_match(tpl, mkdate(2000, 2, 13)));
	return 0;
}

char *test_is_match_yyyymmdd_repeat(void) {
	struct tpl tpl = mktpl();
	tpl.year = 1999;
	tpl.month = 2;
	tpl.day = 13;
	tpl.repeat = 2;

	mu_assert("date does match", is_match(tpl, mkdate(1999, 2, 13)));
	mu_assert("two weeks later does match", is_match(tpl, mkdate(1999, 2, 27)));
	mu_assert("next day does not match", !is_match(tpl, mkdate(1999, 2, 14)));
	mu_assert("one week later does not match", !is_match(tpl, mkdate(1999, 2, 20)));
	return 0;
}

char *test_is_match_weekday(void) {
	struct tpl tpl = mktpl();
	tpl.weekday = 7;

	mu_assert("date does match", is_match(tpl, mkdate(1999, 2, 13)));
	mu_assert("next day does not match", !is_match(tpl, mkdate(1999, 2, 14)));
	return 0;
}

char *test_is_match_weekday_with_nth_of_month(void) {
	struct tpl tpl = mktpl();
	tpl.weekday = 7;
	tpl.nth_of_month = 2;

	mu_assert("date does match", is_match(tpl, mkdate(1999, 2, 13)));
	mu_assert("next day does not match", !is_match(tpl, mkdate(1999, 2, 14)));
	mu_assert("one week later does not match", !is_match(tpl, mkdate(1999, 2, 20)));
	return 0;
}

char *test_is_match_weekday_with_nth_last_of_month(void) {
	struct tpl tpl = mktpl();
	tpl.weekday = 7;
	tpl.nth_of_month = -2;

	mu_assert("date does match", is_match(tpl, mkdate(1999, 2, 20)));
	mu_assert("next day does not match", !is_match(tpl, mkdate(1999, 2, 21)));
	mu_assert("one week later does not match", !is_match(tpl, mkdate(1999, 2, 27)));
	return 0;
}

char *test_is_match_mm_weekday(void) {
	struct tpl tpl = mktpl();
	tpl.month = 2;
	tpl.weekday = 7;
	tpl.nth_of_month = 2;

	mu_assert("date does match", is_match(tpl, mkdate(1999, 2, 13)));
	mu_assert("next day does not match", !is_match(tpl, mkdate(1999, 2, 14)));
	mu_assert("one week later does not match", !is_match(tpl, mkdate(1999, 2, 20)));
	mu_assert("next month does not match", !is_match(tpl, mkdate(1999, 3, 13)));
	return 0;
}

char *test_is_match_yyyymm_weekday(void) {
	struct tpl tpl = mktpl();
	tpl.year = 1999;
	tpl.month = 2;
	tpl.weekday = 7;
	tpl.nth_of_month = 2;

	mu_assert("date does match", is_match(tpl, mkdate(1999, 2, 13)));
	mu_assert("next day does not match", !is_match(tpl, mkdate(1999, 2, 14)));
	mu_assert("one week later does not match", !is_match(tpl, mkdate(1999, 2, 20)));
	mu_assert("next month does not match", !is_match(tpl, mkdate(1999, 3, 13)));
	mu_assert("next year does not match", !is_match(tpl, mkdate(2000, 2, 13)));
	return 0;
}

char *test_is_match_easter(void) {
	struct tpl tpl = mktpl();
	tpl.from_easter = 0;
	tpl.easter = true;

	mu_assert("date does match", is_match(tpl, mkdate(2000, 4, 23)));
	mu_assert("two days later does not match", !is_match(tpl, mkdate(2000, 4, 25)));
	return 0;
}

char *test_is_match_easter_with_offset(void) {
	struct tpl tpl = mktpl();
	tpl.from_easter = 2;
	tpl.easter = true;

	mu_assert("two days later does match", is_match(tpl, mkdate(2000, 4, 25)));
	mu_assert("date does not match2", !is_match(tpl, mkdate(2000, 4, 23)));
	return 0;
}

char *test_is_match_paskha(void) {
	struct tpl tpl = mktpl();
	tpl.from_paskha = 0;
	tpl.paskha = true;

	mu_assert("date does match", is_match(tpl, mkdate(2000, 4, 30)));
	mu_assert("two days earlier does not match", !is_match(tpl, mkdate(2000, 4, 28)));
	return 0;
}

char *test_is_match_paskha_with_offset(void) {
	struct tpl tpl = mktpl();
	tpl.from_paskha = -2;
	tpl.paskha = true;

	mu_assert("two days earlier does match", is_match(tpl, mkdate(2000, 4, 28)));
	mu_assert("date does not match", !is_match(tpl, mkdate(2000, 4, 30)));
	return 0;
}

int main(int argc, char **argv) {
	mu_unit("easter()");
	mu_test("returns correct date for easter", test_easter);
	mu_test("returns correct date for paskha", test_paskha);

	mu_unit("parse_date()");
	mu_test("parses dd", test_parse_date_dd);
	mu_test("parses dd*", test_parse_date_dd_star);
	mu_test("parses mm/dd", test_parse_date_mmdd);
	mu_test("parses mm/dd*", test_parse_date_mmdd_star);
	mu_test("parses yyyy/mm/dd", test_parse_date_yyyymmdd);
	mu_test("parses yyyy/mm/dd*", test_parse_date_yyyymmdd_star);
	mu_test("parses yyyy/mm/dd+n", test_parse_date_yyyymmdd_repeat);
	mu_test("parses weekday", test_parse_date_weekday);
	mu_test("parses weekday+n", test_parse_date_weekday_with_nth_of_month);
	mu_test("parses weekday-n", test_parse_date_weekday_with_nth_last_of_month);
	mu_test("parses mm/weekday", test_parse_date_mm_weekday);
	mu_test("parses yyyy/mm/weekday", test_parse_date_yyyymm_weekday);
	mu_test("parses easter", test_parse_date_easter);
	mu_test("parses easter+n", test_parse_date_easter_with_offset);

	mu_unit("is_match()");
	mu_test("matches dd", test_is_match_dd);
	mu_test("matches mm/dd", test_is_match_mmdd);
	mu_test("matches yyyy/mm/dd", test_is_match_yyyymmdd);
	mu_test("matches yyyy/mm/dd+n", test_is_match_yyyymmdd_repeat);
	mu_test("matches weekday", test_is_match_weekday);
	mu_test("matches weekday+n", test_is_match_weekday_with_nth_of_month);
	mu_test("matches weekday-n", test_is_match_weekday_with_nth_last_of_month);
	mu_test("matches mm/weekday", test_is_match_mm_weekday);
	mu_test("matches yyyy/mm/weekday", test_is_match_yyyymm_weekday);
	mu_test("matches easter", test_is_match_easter);
	mu_test("matches easter+n", test_is_match_easter_with_offset);
	mu_test("matches paskha", test_is_match_paskha);
	mu_test("matches paskha+n", test_is_match_paskha_with_offset);

	printf("Tests run: %d\n", tests_run);
	if (tests_failed) {
		printf("Tests failed: %d\n", tests_failed);
		return EXIT_FAILURE;
	}
}
