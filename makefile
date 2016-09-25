all:	run

build:
	gcc src/shell.c -lreadline -o bin/shell.out

run: build
	bin/shell.out

clear:
	rm bin/*.out
