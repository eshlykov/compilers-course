#pragma once

#include "statement.hpp"
#include "expression.hpp"
#include <memory>
#include <string>

namespace Ast {

    class AssignmentStatement : public Statement {
    public:
        AssignmentStatement(Location location,
            const std::string& variable,
            std::unique_ptr<Expression> expression);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::string variable_;
        const std::unique_ptr<Expression> expression_;
    };

}
