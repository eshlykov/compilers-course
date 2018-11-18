#pragma once

#include "node.hpp"
#include "statement.hpp"
#include <memory>
#include <string>

class MainClass : public Node {
public:
    MainClass(Location location,
        const std::string& className,
        const std::string& argv,
        std::unique_ptr<Statement> mainBody) :
            className_{className},
            argv_{argv},
            mainBody_{std::move(mainBody)} {
        location_ = location;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    const std::string className_;
    const std::string argv_;
    std::unique_ptr<Statement> mainBody_;
};
