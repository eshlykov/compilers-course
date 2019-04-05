#pragma once

#include "../visitor/visitor.hpp"
#include <cassert>

namespace Ct {

    class Node {
    public:
        Node() = default;

        virtual ~Node() = default;

        virtual void Accept(Visitor*) = 0;
    };

}
