#pragma once

class MethodDeclaration;

class MethodDeclarationRepeated {
public:
    MethodDeclarationRepeated() = default;

    explicit MethodDeclarationRepeated(const std::vector<MethodDeclaration*>& methodDeclarationRepeated) :
        methodDeclarationRepeated_{methodDeclarationRepeated} {
    }

public:
    std::vector<MethodDeclaration*> methodDeclarationRepeated_ = {};
};
