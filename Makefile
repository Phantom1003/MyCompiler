LEX=flex
YACC=bison
CC=g++
Obj=test

$(Obj): lex.cpp yac.cpp
	$(CC) -w main.cpp lex.cpp yac.cpp -o $(Obj) -std=c++11

lex.cpp: token.l yac.cpp
	$(LEX) -o lex.cpp token.l

yac.cpp: parser.y
	$(YACC) -dytv -o yac.cpp  parser.y

clean:
	@rm -rf $(Obj) *.o *.output lex.cpp yac.cpp yac.hpp