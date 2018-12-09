#include "label.hpp"

namespace Irt {

    Label::Label(const std::string& label) :
        label_{label} {
    }

    void Label::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
