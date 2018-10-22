#pragma once

#include <memory>

class Type;
class Identifier;

class VarDeclaration {
public:
    VarDeclaration(std::shared_ptr<Type> type, std::shared_ptr<Identifier> varName) :
        type_{type}, varName_{varName} {
    }

public:
    std::shared_ptr<Type> type_ = {};
    std::shared_ptr<Identifier> varName_ = {};
};
