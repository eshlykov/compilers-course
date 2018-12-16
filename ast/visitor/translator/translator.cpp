#include "translator.hpp"

namespace Ast {

    void Translator::Visit(AssignmentByIndexStatement* node) {
    }

    void Translator::Visit(AssignmentStatement* node) {
    }

    void Translator::Visit(BinaryOperatorExpression* node) {
        node->lhs_->Accept(this);
        std::shared_ptr<Irt::Expression> lhs = wrapper_->ToRValue();

        node->rhs_->Accept(this);
        std::shared_ptr<Irt::Expression> rhs = wrapper_->ToRValue();

        switch (node->binaryOperator_) {
        case Ast::BinaryOperator::And:
            wrapper_ = std::make_shared<Irt::AndOperatorWrapper>(
                lhs,
                rhs
            );
            break;
        case Ast::BinaryOperator::Less:
            wrapper_ = std::make_shared<Irt::ComparisonOperatorWrapper>(
                Irt::LogicalOperator::Less,
                lhs,
                rhs
            );
            break;
        default:
            {
                std::optional<Irt::ArithmeticOperator> arithmeticOperator = ToIrtArithmeticOperator(node->binaryOperator_);
                assert(arithmeticOperator.has_value());
                wrapper_ = std::make_shared<Irt::ExpressionWrapper>(
                    std::make_shared<Irt::BinaryOperator>(
                        arithmeticOperator.value(),
                        lhs,
                        rhs
                    )
                );
                break;
            }
        }
    }

    void Translator::Visit(BooleanExpression* node) {
        wrapper_ = std::make_shared<Irt::ExpressionWrapper>(
            std::make_shared<Irt::Constant>(
                node->value_ ? 1 : 0
            )
        );
    }

    void Translator::Visit(ClassBody* node) {
    }

    void Translator::Visit(ClassDeclaration* node) {
    }

    void Translator::Visit(ConditionStatement* node) {
    }

    void Translator::Visit(IdentifierExpression* node) {
    }

    void Translator::Visit(IndexExpression* node) {
        node->lhs_->Accept(this);
        std::shared_ptr<Irt::Expression> array = wrapper_->ToRValue();

        node->rhs_->Accept(this);
        std::shared_ptr<Irt::Expression> index = wrapper_->ToRValue();

        wrapper_ = std::make_shared<Irt::ExpressionWrapper>(
            std::make_shared<Irt::BinaryOperator>(
                Irt::ArithmeticOperator::Plus,
                array,
                std::make_shared<Irt::BinaryOperator>(
                    Irt::ArithmeticOperator::Multiplication,
                    index,
                    std::make_shared<Irt::Constant>(
                        Irt::Frame::WordSize_
                    )
                )
            )
        );
    }

    void Translator::Visit(IntArrayConstructorExpression* node) {
    }

    void Translator::Visit(LengthExpression* node) {
    }

    void Translator::Visit(LoopStatement* node) {
        node->condition_->Accept(this);

        Irt::Address addressIf;
        Irt::Address addressElse;
        std::shared_ptr<Irt::Statement> condition = wrapper_->ToCondtion(addressIf, addressElse);

        node->statement_->Accept(this);

        Irt::Address addressCondition;

        statement_ = std::make_shared<StatementSequence>(
            std::make_shared<Label>(addressCondition),
            std::make_shared<StatementSequence>(
                condition,
                std::make_shared<StatementSequence>(
                    std::make_shared<Label>(addressIf),
                    std::make_shared<StatementSequence>(
                        statement_,
                        std::make_shared<StatementSequence>(
                            std::make_shared<Jump>(addressCondition>,
                            std::make_shared<Label>(addressElse),
                        )
                    )
                )
            )
        );
    }

    void Translator::Visit(MainClass* node) {
    }

    void Translator::Visit(MethodBody* node) {
    }

    void Translator::Visit(MethodCallExpression* node) {
    }

    void Translator::Visit(MethodDeclaration* node) {
    }

    void Translator::Visit(NotExpression* node) {
    }

    void Translator::Visit(NumberExpression* node) {
        wrapper_ = std::make_shared<Irt::ExpressionWrapper>(
            std::make_shared<Irt::Constant>(
                node->value_
            )
        );
    }

    void Translator::Visit(PrintStatement* node) {
    }

    void Translator::Visit(Program* node) {
    }

    void Translator::Visit(ScopeStatement* node) {
    }

    void Translator::Visit(ThisExpression* node) {
    }

    void Translator::Visit(Type* node) {
    }

    void Translator::Visit(UserTypeConstructorExpression* node) {
    }

    void Translator::Visit(VarDeclaration* node) {
    }

    std::optional<Irt::ArithmeticOperator> Translator::ToIrtArithmeticOperator(BinaryOperator binaryOperator) {
        if (binaryOperator == BinaryOperator::Plus) {
            return Irt::ArithmeticOperator::Plus;
        } else if (binaryOperator == BinaryOperator::Minus) {
            return Irt::ArithmeticOperator::Minus;
        } else if (binaryOperator == BinaryOperator::Star) {
            return Irt::ArithmeticOperator::Multiplication;
        }
        return {};
    }

}
