#pragma once

class VarDeclaration;

class VarDeclarationRepeated {
public:
    explicit VarDeclarationRepeated(const std::vector<VarDeclaration*>& varDeclarationRepeated) :
        varDeclarationRepeated_{varDeclarationRepeated} {
    }

public:
    std::vector<VarDeclaration*> varDeclarationRepeated_ = {};
};
