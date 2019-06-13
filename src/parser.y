%{
/*__________ The C Declarations Section __________*/
#include <iostream>
#include <memory>
#include <ast/node/program.hpp>
#include "parser.hpp"

// used to prevent applying name-mangling to the yylex identifier
extern "C" int yylex();
extern "C" FILE* yyin;

using namespace Ast;

void yyerror( Program** root, const char* message ) {
    std::cout << "Parse error at line " << yylloc.first_line << ".  Message: " << message << std::endl;
}

Location ToLocation( YYLTYPE yylloc ) {
    return Location( yylloc.first_line, yylloc.last_line,
        yylloc.first_column, yylloc.last_column );
}
%}

/*__________ The Bison Declarations Section __________*/

// This is the best place to write dependency code required for YYSTYPE and YYLTYPE.
// In other words, it’s the best place to define types referenced in %union directives.
%code requires {
    #include <ast/node/access-modifier.hpp>
    #include <ast/node/expression.hpp>
    #include <ast/node/expression-list.hpp>
    #include <ast/node/statement.hpp>
    #include <ast/node/statement-list.hpp>
    #include <ast/node/type-modifier.hpp>
    #include <ast/node/var-declaration.hpp>
    #include <ast/node/var-declaration-list.hpp>
    #include <ast/node/method-argument.hpp>
    #include <ast/node/method-argument-list.hpp>
    #include <ast/node/method-declaration.hpp>
    #include <ast/node/method-declaration-list.hpp>
    #include <ast/node/main-class.hpp>
    #include <ast/node/class-declaration.hpp>
    #include <ast/node/class-declaration-list.hpp>
    #include <ast/node/program.hpp>
    #include <ast/node/visitor-target.hpp>
    using namespace Ast;
}

// Declare that one or more argument-declaration are additional yyparse arguments.
// The argument-declaration is used when declaring functions or prototypes.
// The last identifier in argument-declaration must be the argument name.
// These are also additional arguments for yyerror function.
%parse-param { Program** root }

%locations

%error-verbose

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype". But tokens could be of any
// arbitrary data type! So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union {
    int                    ival;
    bool                   bval;
    char*                  sval;
    AccessModifier*        accessMod;
    Expression*            exp;
    ExpressionList*        expList;
    Statement*             statement;
    StatementList*         statements;
    TypeModifier*          type;
    VarDeclaration*        varDecl;
    VarDeclarationList*    varDecls;
    MethodArgument*        methodArg;
    MethodArgumentList*    methodArgs;
    MethodDeclaration*     methodDecl;
    MethodDeclarationList* methodDecls;
    MainClass*             mainClass;
    ClassDeclaration*      classDecl;
    ClassDeclarationList*  classDecls;
    Program*               program;
}

// Precedence and associativity of the operators
// http://www.cs.bilkent.edu.tr/~guvenir/courses/CS101/op_precedence.html
%left '='
%left OR
%left AND
%left '<'
%left '+' '-'
%left '*' '/' '%'
%right '!'
%left '[' '.' '('

// define the constant-string tokens:
%token AND
%token OR
%token CLASS
%token PUBLIC
%token PRIVATE
%token STATIC
%token VOID
%token MAIN
%token EXTENDS
%token RETURN
%token IF
%token ELSE
%token WHILE
%token SOUT
%token LENGTH
%token NEW
%token THIS
%token STRING
%token BOOLEAN
%token INT
// define the "terminal symbol" token types we're going to use (in CAPS by convention),
// and associate each with a field of the union:
%token <ival> INTEGER_LITERAL
%token <bval> LOGIC_LITERAL
%token <sval> ID

// define types for all the nonterminal symbols
%type <accessMod>   AccessModifier;
%type <ival>        IntegerLiteral;
%type <exp>         Expression;
%type <expList>     Expressions ExpressionsNonEmpty;
%type <statement>   Statement;
%type <statements>  Statements;
%type <type>        Type;
%type <varDecl>     VarDeclaration;
%type <varDecls>    VarDeclarations;
%type <methodArg>   MethodArgument;
%type <methodArgs>  MethodArguments MethodArgumentsNonEmpty;
%type <methodDecl>  MethodDeclaration;
%type <methodDecls> MethodDeclarations;
%type <mainClass>   MainClass;
%type <classDecl>   ClassDeclaration;
%type <classDecls>  ClassDeclarations;
%type <program>     Program;

%%
/*__________ The Grammar Rules Section __________*/
Program:
      MainClass ClassDeclarations
        { $$ = new Program( $1, $2, ToLocation( @$ ) ); *root = $$; }
    ;

MainClass:
      CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '['']' ID ')' '{' Statements '}' '}'
        {
            $$ = new MainClass(
                new IdExpression( $2, ToLocation( @2 ) ),
                new IdExpression( $12, ToLocation( @12 ) ),
                $15,
                ToLocation( @$ )
            );
            free( $2 );
            free( $12 );
        }
    ;

ClassDeclarations:
      %empty
        { $$ = new ClassDeclarationList( ToLocation( @$ ) ); }
    | ClassDeclarations ClassDeclaration
        { $$ = $1; $$->Add( $2 ); }
    ;

ClassDeclaration:
      CLASS ID '{' VarDeclarations MethodDeclarations '}'
        {
            $$ = new ClassDeclaration( new IdExpression( $2, ToLocation( @2 ) ), $4, $5, ToLocation( @$ ) );
            free( $2 );
        }
    | CLASS ID EXTENDS ID '{' VarDeclarations MethodDeclarations '}'
        {
            $$ = new ClassDeclaration(
                new IdExpression( $2, ToLocation( @2 ) ),
                $6,
                $7,
                new IdExpression( $4, ToLocation( @4 ) ),
                ToLocation( @$ )
            );
            free( $2 );
            free( $4 );
        }
    ;

MethodDeclarations:
      %empty
        { $$ = new MethodDeclarationList( ToLocation( @$ ) ); }
    | MethodDeclarations MethodDeclaration
        { $$ = $1; $$->Add( $2 ); }
    ;

MethodDeclaration:
      AccessModifier Type ID '(' MethodArguments ')' '{' VarDeclarations Statements RETURN Expression ';' '}'
        {
            $$ = new MethodDeclaration(
                $1,
                $2,
                new IdExpression( $3, ToLocation( @3 ) ),
                $5,
                $8,
                $9,
                $11,
                ToLocation( @$ )
            );
            free( $3 );
        }
    ;

VarDeclarations:
      %empty
        { $$ = new VarDeclarationList( ToLocation( @$ ) ); }
    | VarDeclarations VarDeclaration
        { $$ = $1; $$->Add( $2 ); }
    ;

VarDeclaration:
      Type ID ';'
        {
            $$ = new VarDeclaration( $1, new IdExpression( $2, ToLocation( @2 ) ), ToLocation( @$ ) );
            free( $2 );
        }
    ;

Type:
      INT '['']'
        { $$ = new IntArrayTypeModifier( ToLocation( @$ ) ); }
    | BOOLEAN
        { $$ = new BooleanTypeModifier( ToLocation( @$ ) ); }
    | INT
        { $$ = new IntTypeModifier( ToLocation( @$ ) ); }
    | ID
        {
            $$ = new IdTypeModifier( new IdExpression( $1, ToLocation( @1 ) ), ToLocation( @$ ) );
            free( $1 );
        }
    ;

AccessModifier:
      PUBLIC
        { $$ = new PublicAccessModifier( ToLocation( @$ ) ); }
    | PRIVATE
        { $$ = new PrivateAccessModifier( ToLocation( @$ ) ); }
    ;

MethodArguments:
      %empty
        { $$ = new MethodArgumentList( ToLocation( @$ ) ); }
    | MethodArgumentsNonEmpty
        { $$ = $1; }
    ;

MethodArgumentsNonEmpty:
      MethodArgument
        { $$ = new MethodArgumentList( ToLocation( @$ ) ); $$->Add( $1 ); }
    | MethodArgumentsNonEmpty ',' MethodArgument
        { $$ = $1; $$->Add( $3 ); }
    ;

MethodArgument:
      Type ID
        {
            $$ = new MethodArgument( $1, new IdExpression( $2, ToLocation( @2 ) ), ToLocation( @$ ) );
            free( $2 );
        }
    ;

// statements have to be reversed in every visitor
Statements:
      %empty
        { $$ = new StatementList( ToLocation( @$ ) ); }
    | Statement Statements
        { $$ = $2; $$->Add( $1 ); }
    ;

Statement:
      '{' Statements '}'
        { $$ = new BracesStatement( $2, ToLocation( @$ ) ); }
    | IF '(' Expression ')' Statement ELSE Statement
        { $$ = new ConditionalStatement( $3, $5, $7, ToLocation( @$ ) ); }
    | WHILE '(' Expression ')' Statement
        { $$ = new WhileLoopStatement( $3, $5, ToLocation( @$ ) ); }
    | SOUT '(' Expression ')' ';'
        { $$ = new PrintStatement( $3, ToLocation( @$ ) ); }
    | ID '=' Expression ';'
        {
            $$ = new AssignIdStatement( new IdExpression( $1, ToLocation( @$ ) ), $3, ToLocation( @$ ) );
            free( $1 );
        }
    | ID '[' Expression ']' '=' Expression ';'
        {
            $$ = new AssignIdWithIndexStatement( new IdExpression( $1, ToLocation( @$ ) ), $3, $6, ToLocation( @$ ));
            free( $1 );
        }
    ;

Expressions:
      %empty
        { $$ = new ExpressionList( ToLocation( @$ ) ); }
    | ExpressionsNonEmpty
        { $$ = $1; }
    ;

ExpressionsNonEmpty:
      Expression
        { $$ = new ExpressionList( $1, ToLocation( @$ ) ); }
    | ExpressionsNonEmpty ',' Expression
        { $$ = $1; $1->Add( $3 ); }
    ;

Expression:
      Expression AND Expression
        { $$ = new BinaryExpression( OperatorTypes::And,   $1, $3, ToLocation( @$ ) ); }
    | Expression OR Expression
        { $$ = new BinaryExpression( OperatorTypes::Or,    $1, $3, ToLocation( @$ ) ); }
    | Expression '<' Expression
        { $$ = new BinaryExpression( OperatorTypes::Less,    $1, $3, ToLocation( @$ ) ); }
    | Expression '+' Expression
        { $$ = new BinaryExpression( OperatorTypes::Plus,  $1, $3, ToLocation( @$ ) ); }
    | Expression '-' Expression
        { $$ = new BinaryExpression( OperatorTypes::Minus, $1, $3, ToLocation( @$ ) ); }
    | Expression '*' Expression
        { $$ = new BinaryExpression( OperatorTypes::Times, $1, $3, ToLocation( @$ ) ); }
    | Expression '/' Expression
        { $$ = new BinaryExpression( OperatorTypes::Div,   $1, $3, ToLocation( @$ ) ); }
    | Expression '%' Expression
        { $$ = new BinaryExpression( OperatorTypes::Mod,   $1, $3, ToLocation( @$ ) ); }

    | Expression '[' Expression ']'
        { $$ = new BracketExpression( $1, $3, ToLocation( @$ ) ); }
    | Expression '.' LENGTH
        { $$ = new LengthExpression( $1, ToLocation( @$ ) ); }
    | Expression '.' ID '(' Expressions ')'
        {
            $$ = new MethodExpression( $1, new IdExpression( $3, ToLocation( @3 ) ), $5, ToLocation( @$ ) );
            free( $3 );
        }

    | IntegerLiteral
        { $$ = new NumberExpression( $1, ToLocation( @$ ) ); }
    | LOGIC_LITERAL
        { $$ = new LogicExpression( $1, ToLocation( @$ ) ); }
    | ID
        {
            $$ = new IdExpression( $1, ToLocation( @$ ) );
            free( $1 );
        }
    | THIS
        { $$ = new ThisExpression( ToLocation( @$ ) ); }
    | NEW INT '[' Expression ']'
        { $$ = new NewArrayExpression( $4, ToLocation( @$ ) ); }
    | NEW ID '(' ')'
        {
            $$ = new NewIdExpression( new IdExpression( $2, ToLocation( @2 ) ), ToLocation( @$ ) );
            free( $2 );
        }
    | '!' Expression
        { $$ = new NegateExpression( $2, ToLocation( @$ ) ); }
    | '(' Expression ')'
        { $$ = $2; }
    ;

IntegerLiteral:
      INTEGER_LITERAL
        { $$ = $1; }
    | '-' INTEGER_LITERAL
        { $$ = -$2; }
    ;
%%
/*__________ The C Code Section __________*/
// moved to main.cpp
