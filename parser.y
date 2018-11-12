%code requires {

#include "ast.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

extern int yylex();
extern char* yytext;
void yyerror(Program*&, const char*);
extern std::string yyline;

}

%{

bool isErroneous = false;

%}


%parse-param {
    Program*& program
}

%union {
    int NumberToken_;
    std::string* IdentifierToken_;

    ClassDeclaration* ClassDeclaration_;
    std::vector<ClassDeclaration*>* ClassDeclarationRepeated_;
    std::vector<Expression*>* CommaExpressionRepeated_;
    std::vector<VarDeclaration*>* CommaTypeIdentifierRepeated_;
    Expression* Expression_;
    std::vector<Expression*>* ExpressionCommaExpressionRepeatedOptional_;
    std::optional<std::string>* ExtendsIdentifierOptional_;
    Program* Goal_;
    std::string* Identifier_;
    MainClass* MainClass_;
    MethodDeclaration* MethodDeclaration_;
    std::vector<MethodDeclaration*>* MethodDeclarationRepeated_;
    int Number_;
    Statement* Statement_;
    std::vector<Statement*>* StatementRepeated_;
    Type* Type_;
    std::vector<VarDeclaration*>* TypeIdentifierCommaTypeIdentifierRepeatedOptional_;
    VarDeclaration* VarDeclaration_;
    std::vector<VarDeclaration*>* VarDeclarationRepeated_;
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

%right TT_Assignment
%left TT_And
%left TT_Less
%left TT_Plus TT_Minus
%left TT_Star
%left TT_Bang
%left TT_Dot
%right TT_LeftParen TT_LeftBracket

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

%destructor {
    delete $$;
}
    TT_Identifier
    Goal
    MainClass
    ExtendsIdentifierOptional
    ClassDeclaration
    VarDeclaration
    MethodDeclaration
    Type
    Statement
    Expression
    Identifier

%destructor {
    if ($$ != nullptr) {
        FreeVector(*$$);
    }
    delete $$;
}
    ClassDeclarationRepeated
    VarDeclarationRepeated
    MethodDeclarationRepeated
    CommaTypeIdentifierRepeated
    TypeIdentifierCommaTypeIdentifierRepeatedOptional
    StatementRepeated
    CommaExpressionRepeated
    ExpressionCommaExpressionRepeatedOptional

%%

Goal :
    MainClass ClassDeclarationRepeated {
        program = new Program{$1, *$2, isErroneous};
        $$ = nullptr;
    }
;

ClassDeclarationRepeated :
    %empty {
        $$ = new std::vector<ClassDeclaration*>{};
    } | ClassDeclarationRepeated ClassDeclaration {
        $1->push_back($2);
        $$ = $1;
    } | ClassDeclarationRepeated TT_RightBrace {
        $$ = $1;
        yyerrok;
    }
;

MainClass :
    TT_Class Identifier TT_LeftBrace
        TT_Public TT_Static TT_Void TT_Main TT_LeftParen TT_String TT_LeftBracket TT_RightBracket Identifier TT_RightParen TT_LeftBrace
            Statement
         TT_RightBrace
    TT_RightBrace {
        $$ = new MainClass{*$2, *$12, $15};
    }
;

ExtendsIdentifierOptional :
    %empty {
        $$ = new std::optional<std::string>{};
    } | TT_Extends Identifier {
        $$ = new std::optional<std::string>{*$2};
    }
;

VarDeclarationRepeated :
    %empty {
        $$ = new std::vector<VarDeclaration*>{};
    } | VarDeclarationRepeated VarDeclaration {
        $1->push_back($2);
        $$ = $1;
    } | VarDeclarationRepeated error TT_Semicolon {
        $$ = $1;
        yyerrok;
    }
;

MethodDeclarationRepeated :
    %empty {
        $$ = new std::vector<MethodDeclaration*>{};
    } | MethodDeclarationRepeated MethodDeclaration {
        $1->push_back($2);
        $$ = $1;
    }
;

ClassDeclaration :
    TT_Class Identifier ExtendsIdentifierOptional TT_LeftBrace
        VarDeclarationRepeated
        MethodDeclarationRepeated
    TT_RightBrace {
        $$ = new ClassDeclaration{*$2, *$3, new ClassBody{*$5, *$6}};
    }
;

VarDeclaration :
    Type Identifier TT_Semicolon {
        $$ = new VarDeclaration{$1, *$2};
    }
;

CommaTypeIdentifierRepeated :
    %empty {
        $$ = new std::vector<VarDeclaration*>{};
    } | CommaTypeIdentifierRepeated TT_Comma Type Identifier {
        $1->push_back(new VarDeclaration{$3, *$4});
        $$ = $1;
    } | CommaTypeIdentifierRepeated error TT_Identifier {
        $$ = $1;
        static_cast<void>($3); // remove warning 'unused value'
        yyerrok;
    }
;

TypeIdentifierCommaTypeIdentifierRepeatedOptional :
    %empty {
        $$ = new std::vector<VarDeclaration*>{};
    } | Type Identifier CommaTypeIdentifierRepeated {
        $3->push_back(new VarDeclaration{$1, *$2});
        $$ = $3;
    }
;

MethodDeclaration :
    TT_Public Type Identifier TT_LeftParen TypeIdentifierCommaTypeIdentifierRepeatedOptional TT_RightParen TT_LeftBrace
        VarDeclarationRepeated
        StatementRepeated
        TT_Return Expression TT_Semicolon
    TT_RightBrace {
        $$ = new MethodDeclaration{$2, *$3, *$5, new MethodBody{*$8, *$9, $11}};
    }
;

Type :
    TT_Int TT_LeftBracket TT_RightBracket {
        $$ = new PrimitiveType{TypeKind::TK_IntArray};
    } | TT_Boolean {
        $$ = new PrimitiveType{TypeKind::TK_Boolean};
    } | TT_Int {
        $$ = new PrimitiveType{TypeKind::TK_Int};
    } | Identifier {
        $$ = new UserType{*$1};
    }
;

StatementRepeated :
    %empty {
        $$ = new std::vector<Statement*>{};
    } | Statement StatementRepeated {
        $2->push_back($1);
        $$ = $2;
    }
;

Statement :
    TT_LeftBrace StatementRepeated TT_RightBrace {
        $$ = new ScopeStatement{*$2};
    } | TT_If TT_LeftParen Expression TT_RightParen Statement TT_Else Statement {
        $$ = new ConditionStatement{$3, $5, $7};
    } | TT_While TT_LeftParen Expression TT_RightParen Statement {
        $$ = new LoopStatement{$3, $5};
    } | TT_Print TT_LeftParen Expression TT_RightParen TT_Semicolon {
        $$ = new PrintStatement{$3};
    } | Identifier TT_Assignment Expression TT_Semicolon {
        $$ = new AssignmentStatement{*$1, $3};
    } | Identifier TT_LeftBracket Expression TT_RightBracket TT_Assignment Expression TT_Semicolon {
        $$ = new AssignmentByIndexStatement{*$1, $3, $6};
    }
;

CommaExpressionRepeated :
    %empty {
        $$ = new std::vector<Expression*>{};
    } | CommaExpressionRepeated TT_Comma Expression {
        $1->push_back($3);
        $$ = $1;
    }
;

ExpressionCommaExpressionRepeatedOptional :
    %empty {
        $$ = new std::vector<Expression*>{};
    } | Expression CommaExpressionRepeated {
        $2->push_back($1);
        $$ = $2;
    }
;

Expression :
    Expression TT_And Expression {
        $$ = new BinaryOperatorExpression{$1, $3, BinaryOperator::BO_And};
    } | Expression TT_Less Expression {
        $$ = new BinaryOperatorExpression{$1, $3, BinaryOperator::BO_Less};
    } | Expression TT_Plus Expression {
        $$ = new BinaryOperatorExpression{$1, $3, BinaryOperator::BO_Plus};
    } | Expression TT_Minus Expression {
        $$ = new BinaryOperatorExpression{$1, $3, BinaryOperator::BO_Minus};
    } | Expression TT_Star Expression {
        $$ = new BinaryOperatorExpression{$1, $3, BinaryOperator::BO_Star};
    } | Expression TT_LeftBracket Expression TT_RightBracket {
        $$ = new IndexExpression{$1, $3};
    } | Expression TT_Dot TT_Length {
        $$ = new LengthExpression{$1};
    } | Expression TT_Dot Identifier TT_LeftParen ExpressionCommaExpressionRepeatedOptional TT_RightParen {
        $$ = new MethodCallExpression{$1, *$3, *$5};
    } | Number {
        $$ =  new NumberExpression{$1};
    } | TT_True {
        $$ = new BooleanExpression{true};
    } | TT_False {
        $$ = new BooleanExpression{false};
    } | Identifier {
        $$ = new IdentifierExpression{*$1};
    } | TT_This {
        $$ = new ThisExpression{};
    } | TT_New TT_Int TT_LeftBracket Expression TT_RightBracket {
        $$ = new IntArrayConstructorExpression{$4};
    } | TT_New Identifier TT_LeftParen TT_RightParen {
        $$ = new UserTypeConstructorExpression{*$2};
    } | TT_Bang Expression {
        $$ = new NotExpression{$2};
    } | TT_LeftParen Expression TT_RightParen {
        $$ = new ParensExpression{$2};
    }
;

Number :
    TT_Number {
        $$ = $1;
    }
;

Identifier :
    TT_Identifier {
        $$ = $1;
    }
;

%%

void yyerror(Program*& program, const char* message) {
    isErroneous = true;

    std::cout << "\033[1;37m:" << yylloc.first_line << ":" << yylloc.first_column;
    if (yylloc.last_column != yylloc.first_column) {
        std::cout << "-" << yylloc.last_column;
    }
    std::cout << ":\033[0m \033[1;31merror:\033[0m\033[1;37m unexpected token '" << yytext << "'\033[0m" << std::endl;

    std::string line = yyline;
    std::replace(line.begin(), line.end(), '\t', ' ');
    line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());

    std::cout << line << std::endl;

    std::cout << std::string(yylloc.first_column - 1, ' ');
    std::cout << "\033[1;32m^" << std::string(yylloc.last_column - yylloc.first_column, '~') << "\033[0m";
    std::cout << std::endl;
}
