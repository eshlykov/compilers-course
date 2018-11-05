#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <string>

class Statement;

class MainClass : public Node {
public:
    MainClass(const std::string& className, const std::string& argv, Statement* mainBody) :
        className_{className}, argv_{argv}, mainBody_{mainBody} {
    }

    ~MainClass() {
        delete mainBody_;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::string className_ = {};
    std::string argv_ = {};
    Statement* mainBody_ = {};
};
