#include "translator.hpp"

namespace Ast {

    void Translator::Visit(AssignmentByIndexStatement* node) {
    }

    void Translator::Visit(AssignmentStatement* node) {
        node->expression_->Accept(this);

        statement_ = std::make_shared<Irt::Move>(
            codeFragment_.frame_->GetData(node->variable_),
            wrapper_->ToRValue()
        );
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
            }
        }
    }

    void Translator::Visit(BooleanExpression* node) {
        wrapper_ = std::make_shared<Irt::ExpressionWrapper>(
            std::make_shared<Irt::Constant>(node->value_ ? 1 : 0)
        );
    }

    void Translator::Visit(ClassBody* node) {
    }

    void Translator::Visit(ClassDeclaration* node) {
    }

    void Translator::Visit(ConditionStatement* node) {
        node->condition_->Accept(this);

        node->ifStatement_->Accept(this);
        std::shared_ptr<Irt::Statement> ifStatement = statement_;

        node->elseStatement_->Accept(this);
        std::shared_ptr<Irt::Statement> elseStatement = statement_;

        Irt::Address addressIf;
        Irt::Address addressElse;
        Irt::Address addressEnd;

        statement_ = std::make_shared<Irt::StatementSequence>(
            wrapper_->ToCondition(addressIf, addressElse),
            std::make_shared<Irt::StatementSequence>(
                std::make_shared<Irt::Label>(addressIf),
                std::make_shared<Irt::StatementSequence>(
                    ifStatement,
                    std::make_shared<Irt::StatementSequence>(
                        std::make_shared<Irt::Jump>(addressEnd),
                        std::make_shared<Irt::StatementSequence>(
                            std::make_shared<Irt::Label>(addressElse),
                            std::make_shared<Irt::StatementSequence>(
                                elseStatement,
                                std::make_shared<Irt::Label>(addressEnd)
                            )
                        )
                    )
                )
            )
        );
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
                    std::make_shared<Irt::Constant>(Irt::Frame::WordSize_)
                )
            )
        );
    }

    void Translator::Visit(IntArrayConstructorExpression* node) {
        node->expression_->Accept(this);

        Irt::Storage size;
        Irt::Storage array;
        Irt::Storage index;
        Irt::Address addressNew{Irt::SystemFunction::New};
        Irt::Address addressCondition;
        Irt::Address addressIf;
        Irt::Address addressElse;

        wrapper_ = std::make_shared<Irt::ExpressionWrapper>(
            std::make_shared<Irt::ExpressionSequence>(
                std::make_shared<Irt::StatementSequence>(
                    std::make_shared<Irt::Move>(
                        std::make_shared<Irt::Temporary>(size),
                        wrapper_->ToRValue()
                    ),
                    std::make_shared<Irt::StatementSequence>(
                        std::make_shared<Irt::Move>(
                            std::make_shared<Irt::Temporary>(array),
                            std::make_shared<Irt::Call>(
                                std::make_shared<Irt::Name>(addressNew),
                                std::vector<std::shared_ptr<Irt::Expression>>{
                                    std::make_shared<Irt::BinaryOperator>(
                                        Irt::ArithmeticOperator::Multiplication,
                                        std::make_shared<Irt::Temporary>(size),
                                        std::make_shared<Irt::Constant>(Irt::Frame::WordSize_)
                                    )
                                }
                            )
                        ),
                        std::make_shared<Irt::StatementSequence>(
                            std::make_shared<Irt::Move>(
                                std::make_shared<Irt::Temporary>(index),
                                std::make_shared<Irt::Constant>(0)
                            ),
                            std::make_shared<Irt::StatementSequence>(
                                std::make_shared<Irt::Label>(addressCondition),
                                std::make_shared<Irt::StatementSequence>(
                                    std::make_shared<Irt::ConditionalJump>(
                                        Irt::LogicalOperator::Less,
                                        std::make_shared<Irt::Temporary>(index),
                                        std::make_shared<Irt::Temporary>(size),
                                        addressIf,
                                        addressElse
                                    ),
                                    std::make_shared<Irt::StatementSequence>(
                                        std::make_shared<Irt::Label>(addressIf),
                                        std::make_shared<Irt::StatementSequence>(
                                            std::make_shared<Irt::Move>(
                                                std::make_shared<Irt::Memory>(
                                                    std::make_shared<Irt::BinaryOperator>(
                                                        Irt::ArithmeticOperator::Plus,
                                                        std::make_shared<Irt::Temporary>(array),
                                                        std::make_shared<Irt::BinaryOperator>(
                                                            Irt::ArithmeticOperator::Multiplication,
                                                            std::make_shared<Irt::Temporary>(index),
                                                            std::make_shared<Irt::Constant>(Irt::Frame::WordSize_)
                                                        )
                                                    )
                                                ),
                                                std::make_shared<Irt::Constant>(0)
                                            ),
                                            std::make_shared<Irt::StatementSequence>(
                                                std::make_shared<Irt::Move>(
                                                    std::make_shared<Irt::Temporary>(index),
                                                    std::make_shared<Irt::BinaryOperator>(
                                                        Irt::ArithmeticOperator::Plus,
                                                        std::make_shared<Irt::Temporary>(index),
                                                        std::make_shared<Irt::Constant>(1)
                                                    )
                                                ),
                                                std::make_shared<Irt::StatementSequence>(
                                                    std::make_shared<Irt::Jump>(addressCondition),
                                                    std::make_shared<Irt::Label>(addressElse)
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                ),
                std::make_shared<Irt::Temporary>(array)
            )
        );
    }

    void Translator::Visit(LengthExpression* node) {
    }

    void Translator::Visit(LoopStatement* node) {
        node->condition_->Accept(this);
        node->statement_->Accept(this);

        Irt::Address addressCondition;
        Irt::Address addressIf;
        Irt::Address addressElse;

        statement_ = std::make_shared<Irt::StatementSequence>(
            std::make_shared<Irt::Label>(addressCondition),
            std::make_shared<Irt::StatementSequence>(
                wrapper_->ToCondition(addressIf, addressElse),
                std::make_shared<Irt::StatementSequence>(
                    std::make_shared<Irt::Label>(addressIf),
                    std::make_shared<Irt::StatementSequence>(
                        statement_,
                        std::make_shared<Irt::StatementSequence>(
                            std::make_shared<Irt::Jump>(addressCondition),
                            std::make_shared<Irt::Label>(addressElse)
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
        node->expression_->Accept(this);

        Irt::Storage storage;
        Irt::Address addressIf;
        Irt::Address addressElse;
        Irt::Address addressEnd;

        wrapper_ = std::make_shared<Irt::ExpressionWrapper>(
            std::make_shared<Irt::ExpressionSequence>(
                std::make_shared<Irt::StatementSequence>(
                    wrapper_->ToCondition(addressIf, addressElse),
                    std::make_shared<Irt::StatementSequence>(
                        std::make_shared<Irt::Label>(addressIf),
                        std::make_shared<Irt::StatementSequence>(
                            std::make_shared<Irt::Move>(
                                std::make_shared<Irt::Temporary>(storage),
                                std::make_shared<Irt::Constant>(0)
                            ),
                            std::make_shared<Irt::StatementSequence>(
                                std::make_shared<Irt::Jump>(addressEnd),
                                std::make_shared<Irt::StatementSequence>(
                                    std::make_shared<Irt::Label>(addressElse),
                                    std::make_shared<Irt::StatementSequence>(
                                        std::make_shared<Irt::Move>(
                                            std::make_shared<Irt::Temporary>(storage),
                                            std::make_shared<Irt::Constant>(1)
                                        ),
                                        std::make_shared<Irt::Label>(addressEnd)
                                    )
                                )
                            )
                        )
                    )
                ),
                std::make_shared<Irt::Temporary>(storage)
            )
        );
    }

    void Translator::Visit(NumberExpression* node) {
        wrapper_ = std::make_shared<Irt::ExpressionWrapper>(
            std::make_shared<Irt::Constant>(node->value_)
        );
    }

    void Translator::Visit(PrintStatement* node) {
    }

    void Translator::Visit(Program* node) {
    }

    void Translator::Visit(ScopeStatement* node) {
        std::shared_ptr<Irt::Statement> scopeStatement = std::make_shared<Irt::Void>(
            std::make_shared<Irt::Constant>(0)
        );

        for (auto&& statement : node->statements_) {
            statement->Accept(this);

            scopeStatement = std::make_shared<Irt::StatementSequence>(
                scopeStatement,
                statement_
            );
        }

        statement_ = scopeStatement;
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
