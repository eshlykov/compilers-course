%{

#include <iostream>
#include <string>
#include <unordered_map>

enum TTokenType {
    TT_Eof = 0,
    TT_Class,
    TT_Public,
    TT_Static,
    TT_Void,
    TT_Main,
    TT_LeftBracket,
    TT_RightBracket,
    TT_LeftParen,
    TT_RightParen,
    TT_LeftBrace,
    TT_RightBrace,
    TT_Return,
    TT_If,
    TT_Print,
    TT_String,
    TT_New,
    TT_Dot,
    TT_Semicolon,
    TT_Extends,
    TT_Length,
    TT_Else,
    TT_While,
    TT_Boolean,
    TT_True,
    TT_False,
    TT_This,
    TT_Int,
    TT_Bang,
    TT_And,
    TT_Less,
    TT_Plus,
    TT_Minus,
    TT_Star,
    TT_Assignment,
    TT_Comma
};

class TFlexLexer : private yyFlexLexer {
public:
    template <typename ...Args>
    TFlexLexer(Args&&... args) :
        yyFlexLexer(std::forward<Args>(args)...) {
    }

    TTokenType GetNextTokenType() {
        return static_cast<TTokenType>(yylex());
    }

    int GetTokenLength() {
        return static_cast<int>(YYLeng());
    }
};

TFlexLexer lexer{};

std::unordered_map<TTokenType, std::string, std::hash<int>> TokenNames{
    { TT_Class, "Class" },
    { TT_Public, "Public" },
    { TT_Static, "Static" },
    { TT_Void, "Void" },
    { TT_Main, "Main" },
    { TT_LeftBracket, "LeftBracket" },
    { TT_RightBracket, "RightBracket" },
    { TT_LeftParen, "LeftParent" },
    { TT_RightParen, "RightParen" },
    { TT_LeftBrace, "LeftBrace" },
    { TT_RightBrace, "RightBrace" },
    { TT_Return, "Return" },
    { TT_If, "If" },
    { TT_Print, "Print "},
    { TT_String, "String" },
    { TT_New, "New" },
    { TT_Dot, "Dot" },
    { TT_Semicolon, "Semicolon" },
    { TT_Extends, "Extends" },
    { TT_Length, "Length" },
    { TT_Else, "Else" },
    { TT_While, "While" },
    { TT_Boolean, "Boolean" },
    { TT_True, "True" },
    { TT_False, "False" },
    { TT_This, "This" },
    { TT_Int, "Int" },
    { TT_Bang, "Bang" },
    { TT_And, "And" },
    { TT_Less, "Less" },
    { TT_Plus, "Plus" },
    { TT_Minus, "Minus" },
    { TT_Star, "Star" },
    { TT_Assignment, "Assignment" },
    { TT_Comma, "Comma" }
};

void DoDummyStuff(TTokenType tokenType, int& index) {
    const int oldIndex = index;
    index += lexer.GetTokenLength();
    std::cout << TokenNames[tokenType] << "[" << oldIndex << ".." << index - 1 << "]" << std::endl;
}

int current_index = 0;

%}

%option noyywrap

%%

[ \t\n\v\r\f]+ {
    current_index += lexer.GetTokenLength();
}

class {
    DoDummyStuff(TT_Class, current_index);
}

public {
    DoDummyStuff(TT_Public, current_index);
}

static {
    DoDummyStuff(TT_Static, current_index);
}

void {
    DoDummyStuff(TT_Void, current_index);
}

main {
    DoDummyStuff(TT_Main, current_index);
}

\[ {
    DoDummyStuff(TT_LeftBracket, current_index);
}

\] {
    DoDummyStuff(TT_RightBracket, current_index);
}

\( {
    DoDummyStuff(TT_LeftParen, current_index);
}

\) {
    DoDummyStuff(TT_RightParen, current_index);
}

{ {
    DoDummyStuff(TT_LeftBrace, current_index);
}

} {
    DoDummyStuff(TT_RightBrace, current_index);
}

return {
    DoDummyStuff(TT_Return, current_index);
}

if {
    DoDummyStuff(TT_If, current_index);
}

System\.out\.println {
    DoDummyStuff(TT_Print, current_index);
}

String {
    DoDummyStuff(TT_String, current_index);
}

new {
    DoDummyStuff(TT_New, current_index);
}

\. {
    DoDummyStuff(TT_Dot, current_index);
}

; {
    DoDummyStuff(TT_Semicolon, current_index);
}

extends {
    DoDummyStuff(TT_Extends, current_index);
}

length {
    DoDummyStuff(TT_Length, current_index);
}

else {
    DoDummyStuff(TT_Else, current_index);
}

while {
    DoDummyStuff(TT_While, current_index);
}

boolean {
    DoDummyStuff(TT_Boolean, current_index);
}

true {
    DoDummyStuff(TT_True, current_index);
}

false {
    DoDummyStuff(TT_False, current_index);
}

this {
    DoDummyStuff(TT_This, current_index);
}

int {
    DoDummyStuff(TT_Int, current_index);
}

! {
    DoDummyStuff(TT_Bang, current_index);
}

&& {
    DoDummyStuff(TT_And, current_index);
}

\< {
    DoDummyStuff(TT_Less, current_index);
}

\+ {
    DoDummyStuff(TT_Plus, current_index);
}

- {
    DoDummyStuff(TT_Minus, current_index);
}

\* {
    DoDummyStuff(TT_Star, current_index);
}

= {
    DoDummyStuff(TT_Assignment, current_index);
}

, {
    DoDummyStuff(TT_Comma, current_index);
}

. {
    current_index += lexer.GetTokenLength();
    std::cout << "Unknown Token" << std::endl;
}

%%

int main(int, char**) {
    while (lexer.GetNextTokenType() != TT_Eof) {
    }
}

