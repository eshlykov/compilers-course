#pragma once

#include "expression.hpp"
#include "statement.hpp"
#include <memory>
#include <string>

class AssignmentByIndexStatement : public Statement {
public:
    AssignmentByIndexStatement(Location location,
        const std::string& array,
        std::unique_ptr<Expression> index,
        std::unique_ptr<Expression> expression);

    virtual void Accept(Visitor* visitor) override final;

public:
    const std::string array_;
    const std::unique_ptr<Expression> index_;
    const std::unique_ptr<Expression> expression_;
};
