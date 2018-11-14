#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include "statement.hpp"
#include <string>

class MainClass : public Node {
public:
    MainClass(const std::string& className,
        const std::string& argv,
        Statement* mainBody) :
            className_{className},
            argv_{argv},
            mainBody_{mainBody} {
    }

    ~MainClass() {
        delete mainBody_;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    const std::string className_;
    const std::string argv_;
    Statement* mainBody_;
};
