#include "name.hpp"

Name::Name(std::shared_ptr<Label> label) :
    label_{label} {
}

void Name::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
