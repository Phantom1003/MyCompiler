#include <iostream>
#include "AST.hpp"	
#include "yac.hpp"

extern int yyparse();

int main(int argc, char **argv) {
 
    yyparse();

    return 0;
}