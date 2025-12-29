compil_repl: object_compil
	gcc -Wall lexer.o postfix.o -o postfix

object_compil:
	gcc -c -Wall postfix.c -o postfix.o
	gcc -c -Wall lexer.c -o lexer.o