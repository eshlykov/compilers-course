#include "node.hpp"

namespace Ast {

    void Node::SetLocation(const Location& location) {
        location_ = location;
    }

    const Location& Node::GetLocation() const {
        return location_;
    }

}