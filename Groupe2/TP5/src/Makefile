CC = gcc
CFLAGS = -Wall
OBJ = repl.o lexer.o postfix.o evaluateur.o variables.o

repl: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o repl

clean:
	rm -f $(OBJ) repl
