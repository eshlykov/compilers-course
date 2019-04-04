#pragma once

#include "../../../utils/ct.hpp"
#include "../visitor.hpp"
#include "move-call.hpp"
#include "expression-call.hpp"
#include "statement-expression-list.hpp"
#include <memory>

namespace Ct {

    class Canonizer : public Visitor {
    public:
        Canonizer();

        virtual void Visit(BinaryOperator*) override final;

        virtual void Visit(Call*) override final;

        virtual void Visit(ConditionalJump*) override final;

        virtual void Visit(Constant*) override final;

        virtual void Visit(ExpressionSequence*) override final;

        virtual void Visit(Jump*) override final;

        virtual void Visit(Label*) override final;

        virtual void Visit(Memory*) override final;

        virtual void Visit(Move*) override final;

        virtual void Visit(Name*) override final;

        virtual void Visit(StatementSequence*) override final;

        virtual void Visit(Temporary*) override final;

        virtual void Visit(Void*) override final;

    private:
        bool IsConst(std::shared_ptr<Statement> statement) {
            auto voidStatement = std::dynamic_pointer_cast<Void>(statement);
            if (voidStatement == nullptr) {
                return false;
            }

            auto constStatement = std::dynamic_pointer_cast<Constant>(voidStatement->expression_);
            return constStatement != nullptr;
        }

        std::shared_ptr<Statement> Sequence(std::shared_ptr<Statement> first, std::shared_ptr<Statement> second) {
            if (IsConst(first)) {
                return second;
            }
            if (IsConst(second)) {
                return first;
            }
            return std::make_shared<StatementSequence>(first, second);
        }

        bool Commute(std::shared_ptr<Statement> first, std::shared_ptr<Statement> second) {
            auto nameStatement = std::dynamic_pointer_cast<Name>(second);
            auto constStatement = std::dynamic_pointer_cast<Constant>(second);
            return IsConst(first) || nameStatement != nullptr || constStatement != nullptr;
        }

        std::shared_ptr<Statement> DoStatement(std::shared_ptr<StatementSequence> statement) {
            return Sequence(DoStatement(statement->leftStatement_), DoStatement(statement->rightStatement_));
        }

        std::shared_ptr<Statement> DoStatement(std::shared_ptr<Move> moveStatement) {
            auto temporary = std::dynamic_pointer_cast<Temporary>(moveStatement->destination_);
            auto call = std::dynamic_pointer_cast<Call>(moveStatement->source_);
            if (temporary != nullptr && call != nullptr) {
                return ReorderStatement(std::make_shared<MoveCall>(temporary, call));
            }

            auto expressionSequence = std::dynamic_pointer_cast<ExpressionSequence>(moveStatement->destination_);
            if (expressionSequence != nullptr) {
                return DoStatement(std::make_shared<StatementSequence>(expressionSequence->statement_,
                    std::make_shared<Move>(expressionSequence->expression_, moveStatement->source_)));
            }

            return ReorderStatement(moveStatement);
        }

        std::shared_ptr<Statement> DoStatement(std::shared_ptr<Void> voidStatement) {
            auto call = std::dynamic_pointer_cast<Call>(voidStatement);
            if (call != nullptr) {
                return ReorderStatement(std::make_shared<ExpressionCall>(call));
            }

            return ReorderStatement(voidStatement);
        }

        std::shared_ptr<Statement> DoStatement(std::shared_ptr<Statement> statement) {
            auto statementSequence = std::dynamic_pointer_cast<StatementSequence>(statement);
            if (statementSequence != nullptr) {
                return DoStatement(statementSequence);
            }

            auto moveStatement = std::dynamic_pointer_cast<Move>(statement);
            if (moveStatement != nullptr) {
                return DoStatement(moveStatement);
            }

            auto voidStatement = std::dynamic_pointer_cast<Void>(statement);
            if (voidStatement != nullptr) {
                return DoStatement(voidStatement);
            }

            return ReorderStatement(statement);
        }

        std::shared_ptr<Statement> ReorderStatement(std::shared_ptr<Statement>) {
            return nullptr;
        }

    private:
        std::shared_ptr<Node> node_;
    };

}
