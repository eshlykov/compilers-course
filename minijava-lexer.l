%{

#include "minijava-parser.tab.h"

#include <cstdlib>
#include <iostream>

%}

%option noyywrap

%%

[ \t\n\v\r\f]+ {
}

0|[1-9][0-9]* {
    yylval.Number = std::atoi(yytext);
    std::cout << "TT_Number(" << yytext << ")" << std::endl;
    return TT_Number;
}

class {
    std::cout << "TT_Class(" << yytext << ")" << std::endl;
    return TT_Class;
}

public {
    std::cout << "TT_Public(" << yytext << ")" << std::endl;
    return TT_Public;
}

static {
    std::cout << "TT_Static(" << yytext << ")" << std::endl;
    return TT_Static;
}

void {
    std::cout << "TT_Void(" << yytext << ")" << std::endl;
    return TT_Void;
}

main {
    std::cout << "TT_Main(" << yytext << ")" << std::endl;
    return TT_Main;
}

\[ {
    std::cout << "TT_LeftBracket(" << yytext << ")" << std::endl;
    return TT_LeftBracket;
}

\] {
    std::cout << "TT_RightBracket(" << yytext << ")" << std::endl;
    return TT_RightBracket;
}

\( {
    std::cout << "TT_LeftParen(" << yytext << ")" << std::endl;
    return TT_LeftParen;
}

\) {
    std::cout << "TT_RightParen(" << yytext << ")" << std::endl;
    return TT_RightParen;
}

\{ {
    std::cout << "TT_LeftBrace(" << yytext << ")" << std::endl;
    return TT_LeftBrace;
}

\} {
    std::cout << "TT_RightBrace(" << yytext << ")" << std::endl;
    return TT_RightBrace;
}

return {
    std::cout << "TT_Return(" << yytext << ")" << std::endl;
    return TT_Return;
}

if {
    std::cout << "TT_If(" << yytext << ")" << std::endl;
    return TT_If;
}

System\.out\.println {
    std::cout << "TT_Print(" << yytext << ")" << std::endl;
    return TT_Print;
}

String {
    std::cout << "TT_String(" << yytext << ")" << std::endl;
    return TT_String;
}

new {
    std::cout << "TT_New(" << yytext << ")" << std::endl;
    return TT_New;
}

\. {
    std::cout << "TT_Dot(" << yytext << ")" << std::endl;
    return TT_Dot;
}

; {
    std::cout << "TT_Semicolon(" << yytext << ")" << std::endl;
    return TT_Semicolon;
}

extends {
    std::cout << "TT_Extends(" << yytext << ")" << std::endl;
    return TT_Extends;
}

length {
    std::cout << "TT_Length(" << yytext << ")" << std::endl;
    return TT_Length;
}

else {
    std::cout << "TT_Else(" << yytext << ")" << std::endl;
    return TT_Else;
}

while {
    std::cout << "TT_While(" << yytext << ")" << std::endl;
    return TT_While;
}

boolean {
    std::cout << "TT_Boolean(" << yytext << ")" << std::endl;
    return TT_Boolean;
}

true {
    std::cout << "TT_True(" << yytext << ")" << std::endl;
    return TT_True;
}

false {
    std::cout << "TT_False(" << yytext << ")" << std::endl;
    return TT_False;
}

this {
    std::cout << "TT_This(" << yytext << ")" << std::endl;
    return TT_This;
}

int {
    std::cout << "TT_Int(" << yytext << ")" << std::endl;
    return TT_Int;
}

! {
    std::cout << "TT_Bang(" << yytext << ")" << std::endl;
    return TT_Bang;
}

&& {
    std::cout << "TT_And(" << yytext << ")" << std::endl;
    return TT_And;
}

\< {
    std::cout << "TT_Less(" << yytext << ")" << std::endl;
    return TT_Less;
}

\+ {
    std::cout << "TT_Plus(" << yytext << ")" << std::endl;
    return TT_Plus;
}

- {
    std::cout << "TT_Minus;(" << yytext << ")" << std::endl;
    return TT_Minus;;
}

\* {
    std::cout << "TT_Star(" << yytext << ")" << std::endl;
    return TT_Star;
}

= {
    std::cout << "TT_Assignment(" << yytext << ")" << std::endl;
    return TT_Assignment;
}

, {
    std::cout << "TT_Comma(" << yytext << ")" << std::endl;
    return TT_Comma;
}

[a-zA-Z_][a-zA-Z_0-9]* {
    yylval.Identifier = yytext;
    std::cout << "TT_Identifier(" << yytext << ")" << std::endl;
    return TT_Identifier;
}

<<EOF>> {
    std::cout << "TT_Eof(" << yytext << ")" << std::endl;
    return TT_Eof;
}

. {
    std::cout << "TT_Error(" << yytext << ")" << std::endl;
    return TT_Error;
}

%%
