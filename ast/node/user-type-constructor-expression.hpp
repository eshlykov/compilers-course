#pragma once

#include "expression.hpp"
#include <string>

namespace Ast {

    class UserTypeConstructorExpression : public Expression {
    public:
        explicit UserTypeConstructorExpression(Location location,
            const std::string& name);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::string name_;
    };

}
