%{

#include <iostream>
#include <cstdlib>

extern int yylex();
void yyerror(const char*);

%}

%union {
    int Number;
    char* Identifier;
}

%start Input

%token <Number> TT_Number
%token <Identifier>  TT_Identifier
%token TT_Eof
%token TT_Class
%token TT_Public
%token TT_Static
%token TT_Void
%token TT_Main
%token TT_LeftBracket
%token TT_RightBracket
%token TT_LeftParen
%token TT_RightParen
%token TT_LeftBrace
%token TT_RightBrace
%token TT_Return
%token TT_If
%token TT_Print
%token TT_String
%token TT_New
%token TT_Dot
%token TT_Semicolon
%token TT_Extends
%token TT_Length
%token TT_Else
%token TT_While
%token TT_Boolean
%token TT_True
%token TT_False
%token TT_This
%token TT_Int
%token TT_Bang
%token TT_And
%token TT_Less
%token TT_Plus
%token TT_Minus
%token TT_Star
%token TT_Assignment
%token TT_Comma
%token TT_Error

%%

Input:
    TT_Eof { }
    | TT_Class { std::cout << "class\n"; }
    | TT_Public { std::cout << "public\n"; }
    | TT_Static { std::cout << "static\n"; }
    | TT_Void { std::cout << "void\n"; }
    | TT_Main { std::cout << "main\n"; }
    | TT_LeftBracket { std::cout << "[\n"; }
    | TT_RightBracket { std::cout << "]\n"; }
    | TT_LeftParen { std::cout << "[\n"; }
    | TT_RightParen { std::cout << "]\n"; }
    | TT_LeftBrace { std::cout << "{\n"; }
    | TT_RightBrace { std::cout << "}\n"; }
    | TT_Return { std::cout << "return\n"; }
    | TT_String { std::cout << "string\n"; }
    | TT_New { std::cout << "new\n"; }
    | TT_Dot { std::cout << ".\n"; }
    | TT_Semicolon { std::cout << ";\n"; }
    | TT_Extends { std::cout << "extends\n"; }
    | TT_Length { std::cout << "length\n"; }
    | TT_Else { std::cout << "else\n"; }
    | TT_While { std::cout << "while\n"; }
    | TT_Boolean { std::cout << "booleand\n"; }
    | TT_True { std::cout << "true\n"; }
    | TT_False { }
    | TT_This { }
    | TT_Int { }
    | TT_Number { }
    | TT_Bang { }
    | TT_And { }
    | TT_Less { }
    | TT_Plus { }
    | TT_Minus { }
    | TT_Star { }
    | TT_Assignment { }
    | TT_Comma { }
    | TT_Error { }
;

%%

void yyerror(const char *message) {
    std::cout << "Error occured: " << message << std::endl;
    std::exit(1);
}
