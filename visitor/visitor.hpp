#pragma once

#include <memory>
#include <stack>
#include "../ast/node.hpp"

class ExpressionAndExpression;

class IVisitor : public std::enable_shared_from_this<IVisitor> {
public:
    virtual void Visit(std::shared_ptr<ExpressionAndExpression>) = 0;

    std::stack<std::shared_ptr<INode>> nodes = {};
};

