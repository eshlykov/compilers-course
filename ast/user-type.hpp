#pragma once

#include "../visitor.hpp"
#include "type.hpp"

class UserType : public Type {
public:
    UserType(const std::string& className) :
        className_{className} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visitor(this);
    }

public:
    std::string className_ = {};
};
