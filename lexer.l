%{

#include "parser.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

int yycolumnno = 0;
Location location;

#define YY_USER_ACTION { \
    if (yylineno != location.lineNumber_) { \
        yycolumnno = 0; \
    } \
    \
    location.lineNumber_ = yylineno; \
    location.firstColumn_ = yycolumnno; \
    location.lastColumn_ = yycolumnno + yyleng - 1; \
    \
    yycolumnno += yyleng; \
}

%}

%option noyywrap
%option yylineno

%%

[ \t\n\v\r\f]+ {
}

0|[1-9][0-9]* {
    yylval.NumberToken_ = std::atoi(yytext);
    return TT_Number;
}

class {
    return TT_Class;
}

public {
    return TT_Public;
}

static {
    return TT_Static;
}

void {
    return TT_Void;
}

main {
    return TT_Main;
}

\[ {
    return TT_LeftBracket;
}

\] {
    return TT_RightBracket;
}

\( {
    return TT_LeftParen;
}

\) {
    return TT_RightParen;
}

\{ {
    return TT_LeftBrace;
}

\} {
    return TT_RightBrace;
}

return {
    return TT_Return;
}

if {
    return TT_If;
}

System\.out\.println {
    return TT_Print;
}

String {
    return TT_String;
}

new {
    return TT_New;
}

\. {
    return TT_Dot;
}

; {
    return TT_Semicolon;
}

extends {
    return TT_Extends;
}

length {
    return TT_Length;
}

else {
    return TT_Else;
}

while {
    return TT_While;
}

boolean {
    return TT_Boolean;
}

true {
    return TT_True;
}

false {
    return TT_False;
}

this {
    return TT_This;
}

int {
    return TT_Int;
}

! {
    return TT_Bang;
}

&& {
    return TT_And;
}

\< {
    return TT_Less;
}

\+ {
    return TT_Plus;
}

- {
    return TT_Minus;;
}

\* {
    return TT_Star;
}

= {
    return TT_Assignment;
}

, {
    return TT_Comma;
}

[a-zA-Z_][a-zA-Z_0-9]* {
    yylval.IdentifierToken_ = new std::string{yytext};
    return TT_Identifier;
}

\/\/.* {
}

. {
    yyerror(parserArgs, "");
}

%%
