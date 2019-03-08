#include "binary-operator.hpp"

namespace Ct {

    BinaryOperator::BinaryOperator(ArithmeticOperator arithmeticOperator,
        std::shared_ptr<Expression> leftExpression,
        std::shared_ptr<Expression> rightExpression) :
            arithmeticOperator_{arithmeticOperator},
            leftExpression_{leftExpression},
            rightExpression_{rightExpression} {
        assert(leftExpression_ != nullptr);
        assert(rightExpression_ != nullptr);
    }

    void BinaryOperator::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

    std::vector<std::shared_ptr<Expression>> BinaryOperator::Kids() {
        return {leftExpression_, rightExpression_};
    }

    std::shared_ptr<Expression> BinaryOperator::Build(const std::vector<std::shared_ptr<Expression>>& expressionList) {
        return std::make_shared<BinaryOperator>(arithmeticOperator_, expressionList[0], expressionList[1]);
    }

}
