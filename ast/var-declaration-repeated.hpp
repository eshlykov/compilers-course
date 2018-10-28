#pragma once

class VarDeclaration;

class VarDeclarationRepeated {
public:
    VarDeclarationRepeated() = default;

    VarDeclarationRepeated(const std::vector<VarDeclaration*>& varDeclarationRepeated) :
        varDeclarationRepeated_{varDeclarationRepeated} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    std::vector<VarDeclaration*> varDeclarationRepeated_ = {};
};
