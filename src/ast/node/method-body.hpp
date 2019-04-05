#pragma once

#include "node.hpp"
#include "var-declaration.hpp"
#include "statement.hpp"
#include "expression.hpp"
#include <memory>
#include <vector>

namespace Ast {

    class MethodBody : public Node {
    public:
        MethodBody(Location location,
            std::vector<std::unique_ptr<VarDeclaration>>& variables,
            std::vector<std::unique_ptr<Statement>>& statements,
            std::unique_ptr<Expression> returnExpression);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::vector<std::unique_ptr<VarDeclaration>> variables_;
        const std::vector<std::unique_ptr<Statement>> statements_;
        const std::unique_ptr<Expression> returnExpression_;
    };

    inline MethodBody::MethodBody(Location location,
        std::vector<std::unique_ptr<VarDeclaration>>& variables,
        std::vector<std::unique_ptr<Statement>>& statements,
        std::unique_ptr<Expression> returnExpression) :
        variables_{std::move(variables)},
        statements_{std::move(statements)},
        returnExpression_{std::move(returnExpression)} {
        SetLocation(location);
        assert(returnExpression_ != nullptr);
    }

    inline void MethodBody::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
