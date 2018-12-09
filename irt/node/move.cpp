#include "move.hpp"

namespace Irt {

    Move::Move(std::shared_ptr<Expression> destination, std::shared_ptr<Expression> source) :
        destination_{destination},
        source_{source} {
    }

    void Move::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
