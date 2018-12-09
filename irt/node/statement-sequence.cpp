#include "statement-sequence.hpp"

namespace Irt {

    StatementSequence::StatementSequence(std::shared_ptr<Statement> leftStatement,
        std::shared_ptr<Statement> rightStatement) :
            leftStatement_{leftStatement},
            rightStatement_{rightStatement} {
        assert(leftStatement_ != nullptr);
        assert(rightStatement_ != nullptr);
    }

    void StatementSequence::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
