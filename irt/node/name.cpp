#include "name.hpp"

namespace Irt {

    Name::Name(std::shared_ptr<Label> label) :
        label_{label} {
        assert(label_ != nullptr);
    }

    void Name::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
