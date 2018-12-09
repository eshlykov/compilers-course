#pragma once

#include "expression.hpp"
#include <memory>

class Label;

class Name : public Expression {
public:
    explicit Name(std::shared_ptr<Label> label);

    virtual void Accept(Visitor* visitor) override final;

public:
    const std::shared_ptr<Label> label_;
};
