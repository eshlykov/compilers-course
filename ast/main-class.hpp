#pragma once

#include "../visitor.hpp"

class Identifier;
class Statement;

class MainClass {
public:
    MainClass(Identifier* className, Identifier* mainArgumentName, Statement* mainBody) :
        className_{className}, mainArgumentName_{mainArgumentName}, mainBody_{mainBody} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Identifier* className_ = {};
    Identifier* mainArgumentName_ = {};
    Statement* mainBody_ = {};
};
