#pragma once

class Type;
class Identifier;

class CommaTypeIdentifier {
public:
    CommaTypeIdentifier(Type* type, Identifier* name) :
        type_{type}, name_{name} {
    }

private:
    Type* type_ = {};
    Identifier* name_ = {};
};
