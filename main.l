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
    TT_Semicolon
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
    { TT_Semicolon, "Semicolon" }
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

. {
    current_index += lexer.GetTokenLength();
    std::cout << "Unknown Token" << std::endl;
}

%%

int main(int, char**) {
    while (lexer.GetNextTokenType() != TT_Eof) {
    }
}
