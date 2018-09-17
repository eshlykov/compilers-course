%{

#include <iostream>
extern int yylex();

%}

%option noyywrap

%%

[ \t\n]         { std::cout << "whitespace" << std::endl; }
[0-9]+\.[0-9]+  { std::cout << "float " << yytext << std::endl; }
[0-9]+          { std::cout << "integer " << yytext << std::endl; }
[a-zA-Z0-9]+    { std::cout << "string " << yytext << std::endl; }

%%

int main(int, char**) {
    while (yylex()) {
    }
}
