#pragma once

#include "expression.hpp"
#include <memory>
#include <string>

class Temporary : public Expression {
public:
    explicit Temporary(const std::string& temporary);

    virtual void Accept(Visitor* visitor) override final;

public:
    const std::string temporary_;
};
