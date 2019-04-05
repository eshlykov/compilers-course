#pragma once

#include "expression.hpp"
#include <memory>
#include <string>
#include <vector>

namespace Ast {

    class MethodCallExpression : public Expression {
    public:
        MethodCallExpression(Location location,
            std::unique_ptr<Expression> expression,
            const std::string& methodName,
            std::vector<std::unique_ptr<Expression>>& argumentsList);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::unique_ptr<Expression> expression_;
        const std::string methodName_;
        const std::vector<std::unique_ptr<Expression>> argumentsList_;
    };

}
