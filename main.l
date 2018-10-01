%{

#include "minijava-parser.h"

#include <iostream>
#include <string>
#include <unordered_map>

using TokenType = yytokentype;

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

TokenType DoDummyStuff(TokenType tokenType) {
    if (tokenType == TT_Identifier) {
        yylval.Identifier = std::string(yytext);
    } else if (tokenType == TT_Number) {
    // When add C++ 17 support
    //    std::string number(yytext);
    //    std::from_chars(text.begin(), text.end(), yylval.Number);
        yylval.Number = std::atoi(yytext);
    }
    return tokenType;
}

%}

%option noyywrap

%%

[ \t\n\v\r\f]+ {
}

class {
    DoDummyStuff(TT_Class);
}

public {
    DoDummyStuff(TT_Public);
}

static {
    DoDummyStuff(TT_Static);
}

void {
    DoDummyStuff(TT_Void);
}

main {
    DoDummyStuff(TT_Main);
}

\[ {
    DoDummyStuff(TT_LeftBracket);
}

\] {
    DoDummyStuff(TT_RightBracket);
}

\( {
    DoDummyStuff(TT_LeftParen);
}

\) {
    DoDummyStuff(TT_RightParen);
}

{ {
    DoDummyStuff(TT_LeftBrace);
}

} {
    DoDummyStuff(TT_RightBrace);
}

return {
    DoDummyStuff(TT_Return);
}

if {
    DoDummyStuff(TT_If);
}

System\.out\.println {
    DoDummyStuff(TT_Print);
}

String {
    DoDummyStuff(TT_String);
}

new {
    DoDummyStuff(TT_New);
}

\. {
    DoDummyStuff(TT_Dot);
}

; {
    DoDummyStuff(TT_Semicolon);
}

extends {
    DoDummyStuff(TT_Extends);
}

length {
    DoDummyStuff(TT_Length);
}

else {
    DoDummyStuff(TT_Else);
}

while {
    DoDummyStuff(TT_While);
}

boolean {
    DoDummyStuff(TT_Boolean);
}

true {
    DoDummyStuff(TT_True);
}

false {
    DoDummyStuff(TT_False);
}

this {
    DoDummyStuff(TT_This);
}

int {
    DoDummyStuff(TT_Int);
}

! {
    DoDummyStuff(TT_Bang);
}

&& {
    DoDummyStuff(TT_And);
}

\< {
    DoDummyStuff(TT_Less);
}

\+ {
    DoDummyStuff(TT_Plus);
}

- {
    DoDummyStuff(TT_Minus);
}

\* {
    DoDummyStuff(TT_Star);
}

= {
    DoDummyStuff(TT_Assignment);
}

, {
    DoDummyStuff(TT_Comma);
}

([1-9]+[0-9]*)|0 {
    DoDummyStuff(TT_Number);
}

. {
}

%%
