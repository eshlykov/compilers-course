#include "sequence.hpp"

namespace Irt {

    Sequence::Sequence(std::shared_ptr<Statement> leftStatement,
        std::shared_ptr<Statement> rightStatement) :
            leftStatement_{leftStatement},
            rightStatement_{rightStatement} {
    }

    void Sequence::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
