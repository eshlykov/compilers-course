#include "node.hpp"

void Node::SetLocation(const Location& location) {
    location_ = location;
}

Location Node::GetLocation() const {
    return location_;
}
