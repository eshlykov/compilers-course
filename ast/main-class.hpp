#pragma once

#include "../visitor.hpp"
#include "node.hpp"

class Statement;

class MainClass : public Node {
public:
    MainClass(const std::string& className, const std::string& argv, Statement* mainBody) :
        className_{className}, argv_{argv}, mainBody_{mainBody} {
    }

    virtual void Accept(IVisitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::string className_ = {};
    std::string argv_ = {};
    Statement* mainBody_ = {};
};
