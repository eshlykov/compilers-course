#include "conditional-jump-converter.hpp"
#include <exception>

namespace Irt {

    ConditionalJumpConverter::ConditionalJumpConverter(std::shared_ptr<Statement> statement) :
        statement_{statement} {
    }

    std::shared_ptr<Expression> ConditionalJumpConverter::ToExpression() const {
        /*Register temporary;
        Address labelIf;
        Address labelElse;
        return std::make_shared<ExpressionSequence>(
            std::make_shared<Move>(
                std::make_shared<Temporary>(labelIf),
                std::make_shared<Constant>(1)
            ),
            std::make_shared<StatementSequence>(
                ToConditionalJump(labelIf, labelFalse),
                std::make_shared<StatementSequence>(
                    std::make_shared<Label>(labelElse),
                    std::make_shared<StatementSequence>(
                        std::make_shared<Move>(
                            std::make_shared<Temporary>(labelIf),
                            std::make_shared<Constant>(0)
                        ),
                        std::make_shared<Label>(labelIf)
                    ),
                    std::make_shared<Temporary>(labelIf)
                )
            )
        );*/
        return nullptr;
    }

    std::shared_ptr<Statement> ConditionalJumpConverter::ToStatement() const {
        throw std::runtime_error{"ConditionalJumpConverter::ToStatement should never be called"};
    }

}
