#pragma once

#include "../visitor.hpp"
#include "node.hpp"

class Identifier;
class Statement;

class MainClass : public Node {
public:
    MainClass(Identifier* className, Identifier* mainArgumentName, Statement* mainBody) :
        className_{className}, mainArgumentName_{mainArgumentName}, mainBody_{mainBody} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Identifier* className_ = {};
    Identifier* mainArgumentName_ = {};
    Statement* mainBody_ = {};
};
