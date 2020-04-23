all: calendar

%: %.c
	gcc -Wall --std=c99 -pedantic -s $< -o $@

run_tests: test
	./test

.PHONY: all run_tests install
