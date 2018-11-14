#pragma once

#include "../visitor.hpp"
#include "type.hpp"

class UserType : public Type {
public:
    explicit UserType(const std::string& className) :
        className_{className} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    const std::string className_;
};
