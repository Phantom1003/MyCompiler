LEX=flex
YACC=bison
CC=gcc
Obj=test

$(Obj): lex.yy.c 
	$(CC) lex.yy.c  -o $(Obj)

lex.yy.c: token.l
	$(LEX) token.l

clean:
	@rm -rf $(Obj) *.o *.h *.c *.output