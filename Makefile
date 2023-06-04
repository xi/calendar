all: calendar

%: %.c
	gcc -Wall --std=c99 -pedantic -O2 -s $< -o $@ -Dbyday

run_tests: test
	./test

.PHONY: all run_tests install
