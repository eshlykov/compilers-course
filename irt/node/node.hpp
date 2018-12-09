#pragma once

#include "../visitor/visitor.hpp"
#include "../utils/address.hpp"
#include "../utils/register.hpp"
#include <cassert>

namespace Irt {

    class Node {
    public:
        Node() = default;

        virtual ~Node() = default;

        virtual void Accept(Visitor*) = 0;
    };

}
