%{

extern int yylex();
void yyerror(const char*) {}

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
    | TT_Eof { }
    | TT_Class { }
    | TT_Public { }
    | TT_Static { }
    | TT_Void { }
    | TT_Main { }
    | TT_LeftBracket { }
    | TT_RightBracket { }
    | TT_LeftParen { }
    | TT_RightParen { }
    | TT_LeftBrace { }
    | TT_RightBrace { }
    | TT_Return { }
    | TT_String { }
    | TT_New { }
    | TT_Dot { }
    | TT_Semicolon { }
    | TT_Extends { }
    | TT_Length { }
    | TT_Else { }
    | TT_While { }
    | TT_Boolean { }
    | TT_True { }
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
