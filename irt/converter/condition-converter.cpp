#include "condition-converter.hpp"
#include <exception>

namespace Irt {

    std::shared_ptr<Expression> ConditionConverter::ToExpression() const {
        Register temporary;
        Address labelIf;
        Address labelElse;
        return std::make_shared<ExpressionSequence>(
            std::make_shared<StatementSequence>(
                std::make_shared<Move>(
                    std::make_shared<Temporary>(temporary),
                    std::make_shared<Constant>(1)
                ),
                std::make_shared<StatementSequence>(
                    ToConditionalJump(labelIf, labelElse),
                    std::make_shared<StatementSequence>(
                        std::make_shared<Label>(labelElse),
                        std::make_shared<StatementSequence>(
                            std::make_shared<Move>(
                                std::make_shared<Temporary>(temporary),
                                std::make_shared<Constant>(0)
                            ),
                            std::make_shared<Label>(labelIf)
                        )
                    )
                )
            ),
            std::make_shared<Temporary>(temporary)
        );
    }

    std::shared_ptr<Statement> ConditionConverter::ToStatement() const {
        return nullptr;
    }

}
