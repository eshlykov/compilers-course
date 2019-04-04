#pragma once

#include "../../../utils/ct.hpp"
#include "../visitor.hpp"
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

        void Next();

    private:
        std::shared_ptr<Node> node_;
    };

}
