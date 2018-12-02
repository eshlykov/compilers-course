#pragma once

#include "node.hpp"
#include "var-declaration.hpp"
#include "statement.hpp"
#include "expression.hpp"

#include <memory>
#include <vector>

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
