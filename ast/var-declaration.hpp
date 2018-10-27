#pragma once

class Type;
class Identifier;

class VarDeclaration {
public:
    VarDeclaration(Type* type, Identifier* varName) :
        type_{type}, varName_{varName} {
    }

public:
    Type* type_ = {};
    Identifier* varName_ = {};
};
