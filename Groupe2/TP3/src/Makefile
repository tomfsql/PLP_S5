compil_repl: object_compil
	gcc -Wall repl.o lexer.o parseur.o -o repl

object_compil:
	gcc -c -Wall repl.c -o repl.o
	gcc -c -Wall lexer.c -o lexer.o
	gcc -c -Wall parseur.c -o parseur.o
	gcc -c -Wall evaluation.c -o evaluation.o