#include "label.hpp"

Label::Label(const std::string& label) :
    label_{label} {
}

void Label::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
