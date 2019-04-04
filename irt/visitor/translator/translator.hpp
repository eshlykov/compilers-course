#pragma once

#include "../visitor.hpp"
#include "../../../utils/irt.hpp"
#include "../../../ct/node/node.hpp"
#include <memory>

namespace Irt {

    class Translator : public Visitor {
        public:
            Translator();

            virtual void Visit(BinaryOperator* node) override final;

            virtual void Visit(Call* node) override final;

            virtual void Visit(ConditionalJump* node) override final;

            virtual void Visit(Constant* node) override final;

            virtual void Visit(ExpressionSequence* node) override final;

            virtual void Visit(Jump* node) override final;

            virtual void Visit(Label* node) override final;

            virtual void Visit(Memory* node) override final;

            virtual void Visit(Move* node) override final;

            virtual void Visit(Name* node) override final;

            virtual void Visit(StatementSequence* node) override final;

            virtual void Visit(Temporary* node) override final;

            virtual void Visit(Void* node) override final;

        private:
            std::shared_ptr<Ct::Node> node_;
    };

}
