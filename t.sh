#!/bin/sh
bison -o yac.cpp  parser.y
flex -o lex.cpp token.l
g++ -w main.cpp lex.cpp yac.cpp -o test -std=c++11 > log.txt
