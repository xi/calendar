/**
 * BSD calendar reimplementation
 *
 * The calendar utility reads events from plain text files and outputs today's
 * events. The files look something like this::
 *
 *     #include <holiday>
 *     #include <birthday>
 *
 *     06/15	June 15
 *     Thu	Every Thursday.
 *     15	15th of every month.
 *
 *     05/Sun+2	second Sunday in May (Muttertag)
 *     04/Sun-1	last Sunday in April
 *
 *     Easter-2	Good Friday (2 days before Easter)
 *     Paskha	Orthodox Easter
 *
 * This implementation adds some new features while dropping others, most
 * notably, the date formats are not completely compatible::
 *
 *     # added formats
 *     1999/06/15	June 15 1999
 *     1999/06/15*	June 15 (usefull for birthdays)
 *     1999/05/Sun+2	second Sunday in May 1999
 *     1999/06/15+2	June 15 1999 and every second week since then
 *     1999/06/15:1999/06/20	From June 15 1999 to June 20 1999
 *
 *     # removed formats (mostly alternative formats)
 *     Jun. 15	06/15
 *     15 June	06/15
 *     Thursday	Thu
 *     June	06/01
 *     15 *	15
 *
 *     May Sun+2	05/Sun+2
 *     04/SunLast	04/Sun-1
 */

#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libgen.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

struct tpl {
	int year;
	int month;
	int day;
	int end_year;
	int end_month;
	int end_day;
	int repeat;
	int weekday;  /* starting with sunday */
	int nth_of_month;
	int from_easter;
	int from_paskha;
	bool easter;
	bool paskha;
};

struct line {
	struct line *next;
	struct tpl tpl;
	char *desc;
};

struct tm mkdate(int year, int month, int day) {
	struct tm tm = {
		.tm_year=year - 1900,
		.tm_mon=month - 1,
		.tm_mday=day,
	};
	mktime(&tm);
	return tm;
}

struct tpl mktpl(void) {
	struct tpl tpl = {
		.year=0,
		.month=0,
		.day=0,
		.end_year=0,
		.end_month=0,
		.end_day=0,
		.repeat=0,
		.weekday=0,
		.nth_of_month=0,
		.from_easter=0,
		.from_paskha=0,
		.easter=false,
		.paskha=false,
	};
	return tpl;
}

struct tm *today(void) {
	time_t t = time(NULL);
	return localtime(&t);
}

struct tm easter(int year, bool paskha) {
	/* https://de.wikipedia.org/wiki/Gau%C3%9Fsche_Osterformel#Eine_erg.C3.A4nzte_Osterformel */
	int k = year / 100;
	int s = 0;
	int m = 15;
	if (!paskha) {
		s = 2 - (3 * k + 3) / 4;
		m = 17 - s - (8 * k + 13) / 25;
	}
	int a = year % 19;
	int d = (19 * a + m) % 30;
	int r = (d + a / 11) / 29;
	int og = 21 + d - r;
	int sz = 7 - (year + year / 4 + s) % 7;
	int oe = 7 - (og - sz) % 7;
	int os = og + oe;

	if (paskha) {
		os += k - year / 400 - 2;
	}

	struct tm tm = mkdate(year, 3, os);

	return tm;
}

struct tm add_days(struct tm date, int days) {
	struct tm tm = {
		.tm_year=date.tm_year,
		.tm_mon=date.tm_mon,
		.tm_mday=date.tm_mday + days,
	};
	mktime(&tm);
	return tm;
}

bool date_comp(struct tm a, struct tm b) {
	return \
		a.tm_year == b.tm_year && \
		a.tm_mon == b.tm_mon && \
		a.tm_mday == b.tm_mday;
}

bool is_match(struct tpl tpl, struct tm date) {
	struct tm reference;
	time_t delta;
	int delta_days;

	if (tpl.end_day) {
		if (tpl.day && tpl.month && tpl.year && tpl.end_month && tpl.end_year) {
			reference = mkdate(tpl.year, tpl.month, tpl.day);
			delta = difftime(mktime(&reference), mktime(&date));
			delta_days = delta / 60 / 60 / 24;
			if (delta_days > 0) {
				return false;
			}

			reference = mkdate(tpl.end_year, tpl.end_month, tpl.end_day);
			delta = difftime(mktime(&reference), mktime(&date));
			delta_days = delta / 60 / 60 / 24;
			if (delta_days < 0) {
				return false;
			}

			return true;
		} else {
			fprintf(stderr, "Error: incomplete range\n");
			exit(1);
		}
	}

	if (tpl.repeat) {
		if (tpl.day && tpl.month && tpl.year) {
			reference = mkdate(tpl.year, tpl.month, tpl.day);
			delta = difftime(mktime(&reference), mktime(&date));
			delta_days = delta / 60 / 60 / 24;
			if (delta_days % (7 * tpl.repeat) != 0) {
				return false;
			}
		} else {
			fprintf(stderr, "Error: repeat used without day, month and year\n");
			exit(1);
		}
	} else {
		if (tpl.day && date.tm_mday != tpl.day) {
			return false;
		} if (tpl.month && date.tm_mon != tpl.month - 1) {
			return false;
		} if (tpl.year && date.tm_year != tpl.year - 1900) {
			return false;
		}
	}

	if (tpl.weekday && date.tm_wday != tpl.weekday - 1) {
		return false;
	}

	if (tpl.nth_of_month) {
		int a = tpl.nth_of_month;
		struct tm outside = add_days(date, -a * 7);
		if (outside.tm_mon == date.tm_mon) {
			return false;
		}

		int b = a < 0 ? a + 1 : a - 1;
		struct tm inside = add_days(date, -b * 7);
		if (inside.tm_mon != date.tm_mon) {
			return false;
		}
	}

	if (tpl.easter) {
		struct tm d = add_days(date, -tpl.from_easter);
		if (!date_comp(easter(d.tm_year + 1900, false), d)) {
			return false;
		}
	}

	if (tpl.paskha) {
		struct tm d = add_days(date, -tpl.from_paskha);
		if (!date_comp(easter(d.tm_year + 1900, true), d)) {
			return false;
		}
	}

	return true;
}

void invalid_date(char *s) {
	fprintf(stderr, "Error: Invalid date template: %s\n", s);
}

struct tpl parse_date(char *s) {
	struct tm *TODAY = today();
	struct tpl tpl = mktpl();

	int n = 0;
	if (strchr(s, '+')) {
		strtok(s, "+");
		char *s_n = strtok(NULL, "");
		if (s_n == NULL) {
			invalid_date(s);
			exit(1);
		}
		n = atoi(s_n);
	} else if (strchr(s, '-')) {
		strtok(s, "-");
		char *s_n = strtok(NULL, "");
		if (s_n == NULL) {
			invalid_date(s);
			exit(1);
		}
		n = -atoi(s_n);
	}

	/* easter */
	if (strcmp(s, "Easter") == 0) {
		tpl.easter = true;
		tpl.from_easter = n;
		return tpl;
	}
	if (strcmp(s, "Paskha") == 0) {
		tpl.paskha = true;
		tpl.from_paskha = n;
		return tpl;
	}

	bool star = strcmp(s + strlen(s) - strlen("*"), "*") == 0;

	struct tm match;

	/* weekday */
	if (strptime(s, "%Y/%m/%a", &match)) {
		tpl.month = match.tm_mon + 1;
		tpl.weekday = match.tm_wday + 1;
		if (!star) {
			tpl.year = match.tm_year + 1900;
		}
		tpl.nth_of_month = n;
		return tpl;
	} else if (strptime(s, "%m/%a", &match)) {
		tpl.month = match.tm_mon + 1;
		tpl.weekday = match.tm_wday + 1;
		tpl.nth_of_month = n;
		return tpl;
	} else if (strptime(s, "%a", &match)) {
		tpl.weekday = match.tm_wday + 1;
		tpl.nth_of_month = n;
		return tpl;
	}

	/* date */
	if (strptime(s, "%Y/%m/%d", &match)) {
		tpl.month = match.tm_mon + 1;
		tpl.day = match.tm_mday;
		if (!star) {
			tpl.year = match.tm_year + 1900;
		}
		if (strchr(s, ':')) {
			strtok(s, ":");
			char *s_n = strtok(NULL, "");
			if (s_n == NULL) {
				invalid_date(s);
				exit(1);
			} else if (strptime(s_n, "%Y/%m/%d", &match)) {
				tpl.end_month = match.tm_mon + 1;
				tpl.end_day = match.tm_mday;
				tpl.end_year = match.tm_year + 1900;
			} else {
				invalid_date(s);
				exit(1);
			}
		}
		tpl.repeat = n;
		return tpl;
	} else if (strptime(s, "%m/%d", &match)) {
		tpl.month = match.tm_mon + 1;
		tpl.day = match.tm_mday;
		if (!star) {
			tpl.year = TODAY->tm_year + 1900;
			if (match.tm_mon < TODAY->tm_mon) {
				tpl.year += 1;
			}
		}
		return tpl;
	} else if (strptime(s, "%d", &match)) {
		tpl.day = match.tm_mday;
		if (!star) {
			tpl.year = TODAY->tm_year + 1900;
		}
		return tpl;
	}

	invalid_date(s);
	exit(1);
}

struct line *parse_line(char *s_line) {
	char *s_date = strtok(s_line, "\t");
	const char *desc = strtok(NULL, "\n");
	struct line *line = (struct line *)malloc(sizeof(struct line));
	line->tpl = parse_date(s_date);
	line->desc = strdup(desc);
	line->next = NULL;
	return line;
}

char *get_cmd(const char *path) {
	char *cmd_tpl = "cpp -P -traditional -I %s -I %s -I %s -I %s %s";
	char *tmp = strdup(path);
	char *dir = dirname(tmp);

	int length = snprintf(NULL, 0, cmd_tpl, dir, "~/.calendar", "/etc/calendar", "/usr/share/calendar", path);
	char* cmd = malloc(length + 1);
	snprintf(cmd, length + 1, cmd_tpl, dir, "~/.calendar", "/etc/calendar", "/usr/share/calendar", path);
	free(tmp);

	return cmd;
}

struct line *get_lines(char *path) {
	char s_line[265];
	struct line *first = NULL;
	struct line *line = NULL;

	char *cmd = get_cmd(path);
	FILE *fp = popen(cmd, "r");
	free(cmd);
	while (fgets(s_line, sizeof(s_line) - 1, fp) != NULL) {
		if (strlen(s_line) > 1) {
			if (!strchr(s_line, '\t')) {
				fprintf(stderr, "Error: Invalid line: %s\n", s_line);
				exit(1);
			} else if (!first) {
				line = parse_line(s_line);
				first = line;
			} else {
				line->next = parse_line(s_line);
				line = line->next;
			}
		}
	}
	pclose(fp);

	return first;
}

void free_lines(struct line *line) {
	if (line) {
		free_lines(line->next);
		free(line->desc);
		free(line);
	}
}

void print_matches(struct tm date, struct line *first) {
	char ds[11];
	strftime(ds, 11, "%a %b %d", &date);

#ifdef byday
	printf("%s\t", ds);
	struct line *line = first;
	bool is_first = true;
	while (line) {
		if (is_match(line->tpl, date)) {
			if (!is_first) printf("; ");
			is_first = false;
			printf("%s", line->desc);
		}
		line = line->next;
	}
	printf("\n");
#else
	struct line *line = first;
	while (line) {
		if (is_match(line->tpl, date)) {
			printf(ds);
			if (!line->tpl.year) {
				printf("*");
			}
			printf("\t%s\n", line->desc);
		}
		line = line->next;
	}
#endif
}

void help() {
	printf(
		"BSD calendar reimplementation\n"
		"usage: calendar [-h] [-B DAYS_BEFORE] [-A DAYS_AFTER]\n"
	);
}

#ifndef test
int main(int argc, char *argv[]) {
	int days_before = 0;
	int days_after = 3;

	int c;
	while ((c = getopt(argc, argv, "hB:A:")) != -1) {
		switch (c) {
			case 'h':
				help();
				return 0;
			case 'B':
				days_before = atoi(optarg);
				break;
			case 'A':
				days_after = 1 + atoi(optarg);
				break;
			case '?':
				exit(EXIT_FAILURE);
		}
	}

	char* path = "~/.calendar/calendar";
	if (argv[optind] != NULL) {
		path = argv[optind];
	}

	struct line *first = get_lines(path);

	struct tm *TODAY = today();

	struct tm day;
	for (int i = -days_before; i < days_after; i++) {
		day = add_days(*TODAY, i);
		print_matches(day, first);
	}

	free_lines(first);
}
#endif
