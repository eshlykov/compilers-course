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
    Input Input {}
    | TT_Eof { std::cout << "eof\n"; }
    | TT_Class { std::cout << "class\n"; }
    | TT_Public { std::cout << "public\n"; }
    | TT_Static { std::cout << "static\n"; }
    | TT_Void { std::cout << "void\n"; }
    | TT_Main { std::cout << "main\n"; }
    | TT_LeftBracket { std::cout << "[\n"; }
    | TT_RightBracket { std::cout << "]\n"; }
    | TT_LeftParen { std::cout << "(\n"; }
    | TT_RightParen { std::cout << ")\n"; }
    | TT_LeftBrace { std::cout << "{\n"; }
    | TT_RightBrace { std::cout << "}\n"; }
    | TT_Return { std::cout << "return\n"; }
    | TT_String { std::cout << "string\n"; }
    | TT_New { std::cout << "new\n"; }
    | TT_Print { std::cout << "System.out.println\n"; }
    | TT_Dot { std::cout << ".\n"; }
    | TT_Semicolon { std::cout << ";\n"; }
    | TT_Extends { std::cout << "extends\n"; }
    | TT_Length { std::cout << "length\n"; }
    | TT_Else { std::cout << "else\n"; }
    | TT_While { std::cout << "while\n"; }
    | TT_Boolean { std::cout << "booleand\n"; }
    | TT_True { std::cout << "true\n"; }
    | TT_False { std::cout << "false\n"; }
    | TT_This { std::cout << "this\n"; }
    | TT_If { std::cout << "if\n"; }
    | TT_Int { std::cout << "int\n"; }
    | TT_Number { std::cout << $1 << std::endl; }
    | TT_Identifier { std::cout << $1 << std::endl; }
    | TT_Bang { std::cout << "!\n"; }
    | TT_And { std::cout << "&&\n"; }
    | TT_Less { std::cout << "<\n"; }
    | TT_Plus { std::cout << "+\n"; }
    | TT_Minus { std::cout << "-\n"; }
    | TT_Star { std::cout << "*\n"; }
    | TT_Assignment { std::cout << ":=\n"; }
    | TT_Comma { std::cout << ",\n"; }
    | TT_Error { yyerror(":("); }
;

Type :
    TT_Int TT_LeftBracket TT_RightBracket {
    } | TT_Boolean {
    } | TT_Int {
    } | Identifier {
    }
;

Statement :
    TT_If TT_LeftParen Expression TT_RightParen Statement TT_Else Statement {
    } | TT_While TT_LeftParen Expression TT_RightParen Statement {
    } | TT_Print TT_LeftParen Statement TT_RightParen TT_Semicolon {
    } | Identifier TT_Assignment Identifier TT_Semicolon {
    } | Identifier TT_LeftBracket Expression TT_RightBracket TT_Assignment Expression TT_Semicolon {
    }
;

Expression :
    Expression TT_And Expression {
    } | Expression TT_Less Expression {
    } | Expression TT_Plus Expression {
    } | Expression TT_Minus Expression {
    } | Expression TT_Star Expression {
    } | Expression TT_LeftBracket Expression TT_RightBracket {
    } | Expression TT_Dot TT_Length {
    } | Number {
    } | TT_True {
    } | TT_False {
    } | Identifier {
    } | TT_This {
    } | TT_New TT_Int TT_LeftBracket Expression TT_RightBracket {
    } | TT_New Identifier TT_LeftParen TT_RightParen {
    } | TT_Bang Expression {
    } | TT_LeftParen Expression TT_RightParen {
    }
;

Number :
    TT_Number {
    }
;

Identifier :
    TT_Identifier {
        std::cout << $1 << std::endl;
    }
;

%%

void yyerror(const char *message) {
    std::cout << "Error occured: " << message << std::endl;
    std::exit(1);
}
