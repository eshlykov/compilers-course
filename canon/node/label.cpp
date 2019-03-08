#include "label.hpp"

namespace Ct {

    Label::Label(const Address& address) :
        address_{address} {
    }

    void Label::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
