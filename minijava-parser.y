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

%start Goal

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

Goal :
    MainClass ClassDeclarationRepeated TT_Eof {
    }
;

ClassDeclarationRepeated :
    %empty {
    } | ClassDeclarationRepeated ClassDeclaration {
    }
;

MainClass :
    TT_Class Identifier TT_LeftBrace TT_Public TT_Static TT_Void TT_Main TT_LeftParen TT_String TT_LeftBracket TT_RightBracket Identifier TT_RightParen TT_LeftBrace Statement TT_RightBrace TT_RightBrace {
    }
;

ExtendsIdentifierOptional :
    %empty {
    } | TT_Extends Identifier {
    }
;

VarDeclarationRepeated :
    %empty {
    } | VarDeclarationRepeated VarDeclaration {
    }
;

MethodDeclarationRepeated :
    %empty {
    } | MethodDeclarationRepeated MethodDeclaration {
    }
;

ClassDeclaration :
    TT_Class Identifier ExtendsIdentifierOptional TT_LeftBrace VarDeclarationRepeated MethodDeclarationRepeated TT_RightBrace {
    }
;

VarDeclaration :
    Type Identifier TT_Semicolon {
    }
;

CommaTypeIdentifierRepeated :
    %empty {
    } | CommaTypeIdentifierRepeated TT_Comma Type Identifier {
    }
;

TypeIdentifierCommaTypeIdentifierRepeatedOptional :
    %empty {
    } | Type Identifier CommaTypeIdentifierRepeated {
    }
;

MethodDeclaration :
        TT_Public Type Identifier TT_LeftParen TypeIdentifierCommaTypeIdentifierRepeatedOptional TT_RightParen TT_LeftBrace VarDeclarationRepeated StatementRepeated TT_Return Expression TT_Semicolon TT_RightBrace {
        }
;

Type :
    TT_Int TT_LeftBracket TT_RightBracket {
    } | TT_Boolean {
    } | TT_Int {
    } | Identifier {
    }
;

StatementRepeated :
    %empty {
    } | StatementRepeated Statement {
    }
;

Statement :
    TT_LeftBrace StatementRepeated TT_RightBrace {
    } | TT_If TT_LeftParen Expression TT_RightParen Statement TT_Else Statement {
    } | TT_While TT_LeftParen Expression TT_RightParen Statement {
    } | TT_Print TT_LeftParen Statement TT_RightParen TT_Semicolon {
    } | Identifier TT_Assignment Identifier TT_Semicolon {
    } | Identifier TT_LeftBracket Expression TT_RightBracket TT_Assignment Expression TT_Semicolon {
    }
;

CommaExpressionRepeated :
    %empty {
    } | CommaExpressionRepeated TT_Comma Expression {
    }
;

ExpressionCommaExpressionRepeatedOptional :
    %empty {
    } | Expression CommaExpressionRepeated {
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
    } | Expression TT_Dot Identifier TT_LeftParen ExpressionCommaExpressionRepeatedOptional TT_RightParen {
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
