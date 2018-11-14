#pragma once

#include "../visitor.hpp"
#include "expression.hpp"
#include "statement.hpp"
#include <memory>
#include <string>

class AssignmentByIndexStatement : public Statement {
public:
    AssignmentByIndexStatement(const std::string& array,
        std::unique_ptr<Expression> index,
        std::unique_ptr<Expression> expression) :
            array_{array},
            index_{std::move(index)},
            expression_{std::move(expression)} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    const std::string array_;
    std::unique_ptr<Expression> index_;
    std::unique_ptr<Expression> expression_;
};
