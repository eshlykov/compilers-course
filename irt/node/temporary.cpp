#include "temporary.hpp"

namespace Irt {

    Temporary::Temporary(Register temporary) :
        temporary_(temporary) {
    }

    void Temporary::Accept(Visitor* visitor) {

    }

}
