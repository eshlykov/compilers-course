#include "move.hpp"

namespace Irt {

    Move::Move(std::shared_ptr<Expression> destination,
        std::shared_ptr<Expression> source) :
            destination_{destination},
            source_{source} {
        assert(destination_ != nullptr);
        assert(source_ != nullptr);
    }

    void Move::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
