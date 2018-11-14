#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <memory>

class Type;

class VarDeclaration : public Node {
public:
    VarDeclaration(std::unique_ptr<Type> type,
        const std::string& name) :
            type_{std::move(type)},
            name_{name} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::unique_ptr<Type> type_;
    const std::string name_;
};
