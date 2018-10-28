%code requires {

#include "ast.hpp"
#include <iostream>
#include <cstdlib>

extern int yylex();
extern char* yytext;
void yyerror(Goal*, const char*);

}

%parse-param {
    Goal*& goal
}

%union {
    int NumberToken_;
    char* IdentifierToken_;

    ClassDeclaration* ClassDeclaration_;
    ClassDeclarationRepeated* ClassDeclarationRepeated_;
    CommaExpressionRepeated* CommaExpressionRepeated_;
    CommaTypeIdentifierRepeated* CommaTypeIdentifierRepeated_;
    Expression* Expression_;
    ExpressionCommaExpressionRepeatedOptional* ExpressionCommaExpressionRepeatedOptional_;
    ExtendsIdentifierOptional* ExtendsIdentifierOptional_;
    Goal* Goal_;
    Identifier* Identifier_;
    MainClass* MainClass_;
    MethodDeclaration* MethodDeclaration_;
    MethodDeclarationRepeated* MethodDeclarationRepeated_;
    Number* Number_;
    Statement* Statement_;
    StatementRepeated* StatementRepeated_;
    Type* Type_;
    TypeIdentifierCommaTypeIdentifierRepeatedOptional* TypeIdentifierCommaTypeIdentifierRepeatedOptional_;
    VarDeclaration* VarDeclaration_;
    VarDeclarationRepeated* VarDeclarationRepeated_;
}

%start Goal

%token <NumberToken_> TT_Number
%token <IdentifierToken_>  TT_Identifier
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

%type <Goal_> Goal
%type <ClassDeclarationRepeated_> ClassDeclarationRepeated
%type <MainClass_> MainClass
%type <ExtendsIdentifierOptional_> ExtendsIdentifierOptional
%type <VarDeclarationRepeated_> VarDeclarationRepeated
%type <MethodDeclarationRepeated_> MethodDeclarationRepeated
%type <ClassDeclaration_> ClassDeclaration
%type <VarDeclaration_> VarDeclaration
%type <CommaTypeIdentifierRepeated_> CommaTypeIdentifierRepeated
%type <TypeIdentifierCommaTypeIdentifierRepeatedOptional_> TypeIdentifierCommaTypeIdentifierRepeatedOptional
%type <MethodDeclaration_> MethodDeclaration
%type <Type_> Type
%type <StatementRepeated_> StatementRepeated
%type <Statement_> Statement
%type <CommaExpressionRepeated_> CommaExpressionRepeated
%type <ExpressionCommaExpressionRepeatedOptional_> ExpressionCommaExpressionRepeatedOptional
%type <Expression_> Expression
%type <Number_> Number
%type <Identifier_> Identifier

%locations

%%

Goal :
    MainClass ClassDeclarationRepeated {
        std::cout << "Goal" << std::endl;
        goal = new Goal{$1, $2};
    }
;

ClassDeclarationRepeated :
    %empty {
        $$ = new ClassDeclarationRepeated{};
    } | ClassDeclarationRepeated ClassDeclaration {
        std::cout << "ClassDeclarationRepeated" << std::endl;
        auto classDeclarationRepeated = $1->classDeclarationRepeated_;
        classDeclarationRepeated.push_back($2);
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
        $$ = new MainClass{$2, $12, $15};
    }
;

ExtendsIdentifierOptional :
    %empty {
        $$ = new ExtendsIdentifierOptional{};
    } | TT_Extends Identifier {
        std::cout << "ExtendsIdentifierOptional" << std::endl;
        $$ = new ExtendsIdentifierOptional{$2};
    }
;

VarDeclarationRepeated :
    %empty {
        $$ = new VarDeclarationRepeated{};
    } | VarDeclarationRepeated VarDeclaration {
        std::cout << "VarDecalarationRepeated" << std::endl;
        auto varDeclarationRepeated = $1->varDeclarationRepeated_;
        varDeclarationRepeated.push_back($2);
        $$ = new VarDeclarationRepeated{varDeclarationRepeated};
    }
;

MethodDeclarationRepeated :
    %empty {
        $$ = new MethodDeclarationRepeated{};
    } | MethodDeclarationRepeated MethodDeclaration {
        std::cout << "MethodDeclarationRepeated" << std::endl;
        auto methodDeclarationRepeated = $1->methodDeclarationRepeated_;
        methodDeclarationRepeated.push_back($2);
        $$ = new MethodDeclarationRepeated(methodDeclarationRepeated);
    }
;

ClassDeclaration :
    TT_Class Identifier ExtendsIdentifierOptional TT_LeftBrace
        VarDeclarationRepeated
        MethodDeclarationRepeated
    TT_RightBrace {
        std::cout << "ClassDeclaration" << std::endl;
        $$ = new ClassDeclaration{$2, $3, $5, $6};
    }
;

VarDeclaration :
    Type Identifier TT_Semicolon {
        std::cout << "VarDeclaration" << std::endl;
        $$ = new VarDeclaration{$1, $2};
    }
;

CommaTypeIdentifierRepeated :
    %empty {
        $$ = new CommaTypeIdentifierRepeated{};
    } | CommaTypeIdentifierRepeated TT_Comma Type Identifier {
        std::cout << "CommaTypeIdentifierRepeated" << std::endl;
        auto* commaTypeIdentifier = new CommaTypeIdentifier{$3, $4};
        auto commaTypeIdentifierRepeated = $1->commaTypeIdentifierRepeated_;
        commaTypeIdentifierRepeated.push_back(commaTypeIdentifier);
        $$ = new CommaTypeIdentifierRepeated(commaTypeIdentifierRepeated);
    }
;

TypeIdentifierCommaTypeIdentifierRepeatedOptional :
    %empty {
        $$ = new TypeIdentifierCommaTypeIdentifierRepeatedOptional{};
    } | Type Identifier CommaTypeIdentifierRepeated {
        std::cout << "TypeIdentifierCommaTypeIdentifierRepeated" << std::endl;
        auto* typeIdentifierCommaTypeIdentifierRepeated = new TypeIdentifierCommaTypeIdentifierRepeated{$1, $2, $3};
        $$ = new TypeIdentifierCommaTypeIdentifierRepeatedOptional{typeIdentifierCommaTypeIdentifierRepeated};
    }
;

MethodDeclaration :
    TT_Public Type Identifier TT_LeftParen TypeIdentifierCommaTypeIdentifierRepeatedOptional TT_RightParen TT_LeftBrace
        VarDeclarationRepeated
        StatementRepeated
        TT_Return Expression TT_Semicolon
    TT_RightBrace {
        std::cout << "MethodDeclaration" << std::endl;
        $$ = new MethodDeclaration{$2, $3, $5, $8, $9, $11};
    }
;

Type :
    TT_Int TT_LeftBracket TT_RightBracket {
        $$ = new TypeIntArray{};
    } | TT_Boolean {
        $$ = new TypeBoolean{};
    } | TT_Int {
        $$ = new TypeInt{};
    } | Identifier {
        std::cout << "Type" << std::endl;
        $$ = new TypeIdentifier{$1};
    }
;

StatementRepeated :
    %empty {
        $$ = new StatementRepeated{};
    } | Statement StatementRepeated {
        std::cout << "StatementRepeated" << std::endl;
        auto statementRepeated = $2->statementRepeated_;
        statementRepeated.push_back($1);
        $$ = new StatementRepeated{statementRepeated};
    }
;

Statement :
    TT_LeftBrace StatementRepeated TT_RightBrace {
        $$ = new BracedStatement{$2};
    } | TT_If TT_LeftParen Expression TT_RightParen Statement TT_Else Statement {
        $$ = new StatementIfElse{$3, $5, $7};
    } | TT_While TT_LeftParen Expression TT_RightParen Statement {
        $$ = new StatementWhile{$3, $5};
    } | TT_Print TT_LeftParen Expression TT_RightParen TT_Semicolon {
        $$ = new StatementPrint{$3};
    } | Identifier TT_Assignment Expression TT_Semicolon {
        $$ = new StatementAssignment{$1, $3};
    } | Identifier TT_LeftBracket Expression TT_RightBracket TT_Assignment Expression TT_Semicolon {
        $$ = new StatementAssignmentArray{$1, $3, $6};
    }
;

CommaExpressionRepeated :
    %empty {
        $$ = new CommaExpressionRepeated{};
    } | CommaExpressionRepeated TT_Comma Expression {
        std::cout << "CommaExpressionRepeated" << std::endl;
        auto commaExpressionRepeated = $1->commaExpression_;
        auto* commaExpression = new CommaExpression{$3};
        commaExpressionRepeated.push_back(commaExpression);
        $$ = new CommaExpressionRepeated{commaExpressionRepeated};
    }
;

ExpressionCommaExpressionRepeatedOptional :
    %empty {
        $$ = new ExpressionCommaExpressionRepeatedOptional{};
    } | Expression CommaExpressionRepeated {
        std::cout << "ExpressionCommaExpressionRepeatedOptional" << std::endl;
        auto* expressionCommeExpressionRepeated = new ExpressionCommaExpressionRepeated{$1, $2};
        $$ = new ExpressionCommaExpressionRepeatedOptional{expressionCommeExpressionRepeated};
    }
;

Expression :
    Expression TT_And Expression {
        $$ = new ExpressionBinaryOperatorExpression{$1, $3, BinaryOperator::BO_And};
    } | Expression TT_Less Expression {
        $$ = new ExpressionBinaryOperatorExpression{$1, $3, BinaryOperator::BO_Less};
    } | Expression TT_Plus Expression {
        $$ = new ExpressionBinaryOperatorExpression{$1, $3, BinaryOperator::BO_Plus};
    } | Expression TT_Minus Expression {
        $$ = new ExpressionBinaryOperatorExpression{$1, $3, BinaryOperator::BO_Minus};
    } | Expression TT_Star Expression {
        $$ = new ExpressionBinaryOperatorExpression{$1, $3, BinaryOperator::BO_Star};
    } | Expression TT_LeftBracket Expression TT_RightBracket {
        $$ = new ExpressionAtExpression{$1, $3};
    } | Expression TT_Dot TT_Length {
        $$ = new ExpressionLength{$1};
    } | Expression TT_Dot Identifier TT_LeftParen ExpressionCommaExpressionRepeatedOptional TT_RightParen {
        $$ = new ExpressionIdentifierExpressionCommaExpressionRepeatedOptional{$1, $3, $5};
    } | Number {
        $$ =  $1;
    } | TT_True {
        $$ = new ExpressionTrue{};
    } | TT_False {
        $$ = new ExpressionFalse{};
    } | Identifier {
        $$ = $1;
    } | TT_This {
        $$ = new ExpressionThis{};
    } | TT_New TT_Int TT_LeftBracket Expression TT_RightBracket {
        $$ = new ExpressionNewExpression{$4};
    } | TT_New Identifier TT_LeftParen TT_RightParen {
        $$ = new ExpressionNewIdentifier{$2};
    } | TT_Bang Expression {
        $$ = new ExpressionBang{$2};
    } | TT_LeftParen Expression TT_RightParen {
        $$ = new ExpressionParentheses{$2};
    }
;

Number :
    TT_Number {
        std::cout << "Number(" << $1 << ")" << std::endl;
        $$ = new Number($1);
    }
;

Identifier :
    TT_Identifier {
        std::cout << "Identifier(" << $1 << ")" << std::endl;
        $$ = new Identifier($1);
    }
;

%%

void yyerror(Goal*, const char* message) {
    std::cout << "Error occured at line: " << yylloc.first_line << std::endl;
    std::cout << "Columns: [" << yylloc.first_column << ": " << yylloc.last_column << "]" << std::endl;
    std::cout << "Error: " << yytext << std::endl;
    std::cout << "Error message: " << message << std::endl;
    std::exit(1);
}
