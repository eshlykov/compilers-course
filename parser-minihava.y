%{

#include <iostream>
#include <cstdlib>

extern int yylex();
extern char* yytext;
void yyerror(const char*);

%}

%union {
    int Number;
    char* Identifier;
}

%start Goal

%token <Number> TT_Number
%token <Identifier>  TT_Identifier
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

%right TT_Assignment
%left TT_And
%left TT_Less
%left TT_Plus TT_Minus
%left TT_Star
%left TT_Bang
%left TT_Dot
%right TTLeftParen TT_LeftBracket

%locations

%%

Goal :
    MainClass ClassDeclarationRepeated {
        std::cout << "Goal" << std::endl;
    }
;

ClassDeclarationRepeated :
    %empty {
        $$ = new ClassDeclarationRepeated{std::vector<ClassDeclaration>{}};
    } | ClassDeclarationRepeated ClassDeclaration {
        std::cout << "ClassDeclarationRepeated" << std::endl;

        auto classDeclarationRepeated = $1->classDeclarationRepeated_;
        classDeclarationRepeated.push_back(std::make_shared<ClassDeclaration>($2));
        $$ = new ClassDeclarationRepeated{classDeclarationRepeated};
    }
;

MainClass :
    TT_Class Identifier TT_LeftBrace
        TT_Public TT_Static TT_Void TT_Main TT_LeftParen TT_String TT_LeftBracket TT_RightBracket Identifier TT_RightParen TT_LeftBrace
            Statement
         TT_RightBrace
    TT_RightBrace {
        std::cout << "MainClass" << std::endl;
    }
;

ExtendsIdentifierOptional :
    %empty {
    } | TT_Extends Identifier {
        std::cout << "ExtendsIdentifierOptional" << std::endl;
    }
;

VarDeclarationRepeated :
    %empty {
    } | VarDeclarationRepeated VarDeclaration {
        std::cout << "VarDecalarationRepeated" << std::endl;
    }
;

MethodDeclarationRepeated :
    %empty {
    } | MethodDeclarationRepeated MethodDeclaration {
        std::cout << "MethodDeclarationRepeated" << std::endl;
    }
;

ClassDeclaration :
    TT_Class Identifier ExtendsIdentifierOptional TT_LeftBrace
        VarDeclarationRepeated
        MethodDeclarationRepeated
    TT_RightBrace {
        std::cout << "ClassDeclaration" << std::endl;
    }
;

VarDeclaration :
    Type Identifier TT_Semicolon {
        std::cout << "VarDeclaration" << std::endl;
    }
;

CommaTypeIdentifierRepeated :
    %empty {
    } | CommaTypeIdentifierRepeated TT_Comma Type Identifier {
        std::cout << "CommaTypeIdentifierRepeated" << std::endl;
    }
;

TypeIdentifierCommaTypeIdentifierRepeatedOptional :
    %empty {
    } | Type Identifier CommaTypeIdentifierRepeated {
        std::cout << "TypeIdentifierCommaTypeIdentifierRepeated" << std::endl;
    }
;

MethodDeclaration :
    TT_Public Type Identifier TT_LeftParen TypeIdentifierCommaTypeIdentifierRepeatedOptional TT_RightParen TT_LeftBrace
        VarDeclarationRepeated
        StatementRepeated
        TT_Return Expression TT_Semicolon
    TT_RightBrace {
        std::cout << "MethodDeclaration" << std::endl;
    }
;

Type :
    TT_Int TT_LeftBracket TT_RightBracket {
        $$ = new Type{};
    } | TT_Boolean {
    } | TT_Int {
    } | Identifier {
        std::cout << "Type" << std::endl;
    }
;

StatementRepeated :
    %empty {
    } | Statement StatementRepeated {
        std::cout << "StatementRepeated" << std::endl;
    }
;

Statement :
    TT_LeftBrace StatementRepeated TT_RightBrace {
    } | TT_If TT_LeftParen Expression TT_RightParen Statement TT_Else Statement {
    } | TT_While TT_LeftParen Expression TT_RightParen Statement {
    } | TT_Print TT_LeftParen Expression TT_RightParen TT_Semicolon {
    } | Identifier TT_Assignment Expression TT_Semicolon {
    } | Identifier TT_LeftBracket Expression TT_RightBracket TT_Assignment Expression TT_Semicolon {
    }
;

CommaExpressionRepeated :
    %empty {
    } | CommaExpressionRepeated TT_Comma Expression {
        std::cout << "CommaExpressionRepeated" << std::endl;
    }
;

ExpressionCommaExpressionRepeatedOptional :
    %empty {
    } | Expression CommaExpressionRepeated {
        std::cout << "ExpressionCommaExpressionRepeatedOptional" << std::endl;
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
        std::cout << "Number(" << $1 << ")" << std::endl;
    }
;

Identifier :
    TT_Identifier {
        std::cout << "Identifier(" << $1 << ")" << std::endl;
    }
;

%%

void yyerror(const char* message) {
    std::cout << "Error occured at line: " << yylloc.first_line << std::endl;
    std::cout << "Columns: [" << yylloc.first_column << ": " << yylloc.last_column << "]" << std::endl;
    std::cout << "Error: " << yytext << std::endl;
    std::cout << "Error message: " << message << std::endl;
    std::exit(1);
}
