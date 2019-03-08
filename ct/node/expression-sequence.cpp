#include "expression-sequence.hpp"

namespace Ct {

    ExpressionSequence::ExpressionSequence(std::shared_ptr<Statement> statement,
        std::shared_ptr<Expression> expression) :
            statement_{statement},
            expression_{expression} {
        assert(statement_ != nullptr);
        assert(expression_ != nullptr);
    }

    void ExpressionSequence::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

    std::vector<std::shared_ptr<Expression>> ExpressionSequence::Kids() {
        return {expression_};
    }

    std::shared_ptr<Expression> ExpressionSequence::Build(const std::vector<std::shared_ptr<Expression>>& expressionList) {
        return std::make_shared<ExpressionSequence>(statement_, expressionList[0]);
    }

}
