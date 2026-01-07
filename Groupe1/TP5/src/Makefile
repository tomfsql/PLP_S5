# Variables
CC = gcc
# Flags: -Wall (Warnings), -g (Debugging info)
CFLAGS = -Wall -Wextra -g

# 2. Default: Runs when you type 'make'
all: repl

# Dependencies: The object files 'parse', 'calc' and the source 'repl.c'
repl: parse calc repl.c
	$(CC) $(CFLAGS) parse calc repl.c -o repl $(LDFLAGS)

parse: parse_npf.c
	$(CC) $(CFLAGS) -c ./parse_npf.c -o parse

calc: calc_npf.c
	$(CC) $(CFLAGS) -c ./calc_npf.c -o calc

# Run the program
run: repl
	./repl

# Clean up command
clean:
	rm -f parse calc repl

.PHONY: all clean run