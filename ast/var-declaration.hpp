#pragma once

class Type;
class Identifier;

class VarDeclaration {
public:
    VarDeclaration(Type* type, Identifier* varName) :
        type_{type}, varName_{varName} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Type* type_ = {};
    Identifier* varName_ = {};
};
