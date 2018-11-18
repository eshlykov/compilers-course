#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <memory>

class Type;

class VarDeclaration : public Node {
public:
    VarDeclaration(Location location,
        std::unique_ptr<Type> type,
        const std::string& name) :
            type_{std::move(type)},
            name_{name} {
        location_ = location;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::unique_ptr<Type> type_;
    const std::string name_;
};
