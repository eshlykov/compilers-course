%{

#include "minijava-parser.h"

#include <charconv>
#include <iostream>
#include <string>

/*using TokenType = yytokentype;

class TFlexLexer : private yyFlexLexer {
public:
    template <typename ...Args>
    TFlexLexer(Args&&... args) :
        yyFlexLexer(std::forward<Args>(args)...) {
    }

    TokenType GetNextTokenType() {
        return static_cast<TokenType>(yylex());
    }

    int GetTokenLength() {
        return static_cast<int>(YYLeng());
    }
};

TFlexLexer lexer{};
*/

%}

%option noyywrap

%%

[ \t\n\v\r\f]+ {
}

[a-zA-z_][a-zA-z_0-9]* {
    yylval.Identifiery = std::string(yytext);
    return TT_Identifier;
}

0|[1-9][0-9]* {
    std::string number(yytext);
    std::from_chars(text.begin(), text.end(), yylval.Number);
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

{ {
    return TT_LeftBrace;
}

} {
    return TT_RightBrace;
}

return {
    return TT_Return;
}

if {
    return TT_If;
}

System\.out\.println {
    return TT_Printl
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
    return TT_Exntends;
}

length {
    return TT_Length;
}

else {
    return TT_Ele;
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

. {
    return TT_Error;
}

%%
