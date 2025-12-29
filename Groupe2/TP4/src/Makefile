compil_repl: object_compil
	gcc -Wall repl.o lexer.o postfix.o evaluateur.o -o repl

object_compil:
	gcc -c -Wall postfix.c -o postfix.o
	gcc -c -Wall lexer.c -o lexer.o
	gcc -c -Wall evaluateur.c -o evaluateur.o
	gcc -c -Wall repl.c -o repl.o