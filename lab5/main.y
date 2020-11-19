%{
    #include <iostream>
    #include <stdio.h>
    #include <stdlib.h>
    using namespace std;

    extern int yylex();
    extern int yyparse();
}