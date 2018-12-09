#include "temporary.hpp"

namespace Irt {

    Temporary::Temporary(const std::string& temporary) :
        temporary_(temporary) {
    }

    void Temporary::Accept(Visitor* visitor) {

    }

}
