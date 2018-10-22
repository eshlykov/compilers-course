#pragma once

#include <memory>
#include "node.hpp"

template <typename T>
class IExpression : public INode {
public:
    explicit IExpression(T&& _value) :
        value{_value} {
    }

    T value = {};
};

