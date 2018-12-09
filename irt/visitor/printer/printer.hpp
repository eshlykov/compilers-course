#pragma once

#include "../../../utils/irt.hpp"
#include "../visitor.hpp"
#include <fstream>
#include <string>

namespace Irt {

    class Printer : public Visitor {
    public:
        explicit Printer(const std::string& filename);

        ~Printer();

        virtual void Visit(BinaryOperator* node) override final;

        virtual void Visit(Call* node) override final;

        virtual void Visit(ConditionalJump*) override final;

        virtual void Visit(Constant* node) override final;

        virtual void Visit(ExpressionSequence*) override final;

        virtual void Visit(Jump* node) override final;

        virtual void Visit(Label* node) override final;

        virtual void Visit(Memory* node) override final;

        virtual void Visit(Move* node) override final;

        virtual void Visit(Name* node) override final;

        virtual void Visit(StatementSequence* node) override final;

        virtual void Visit(Temporary* node) override final;

        virtual void Visit(Void* node) override final;

    private:
        void PrintHead(int headNodeNumber, const std::string& label);

        void PrintEdge(int headNodeNumber);

        void PrintLeaf(int headNodeNumber, const std::string& label, const std::string& name);

    private:
        std::ofstream file_;
        int nodeNumber_;
    };

}
