#pragma once

#include "../../utils/irt.hpp"
#include "../ir-visitor.hpp"
#include <fstream>
#include <string>

class IrPrinter : public IrVisitor {
public:
    explicit IrPrinter(const std::string& filename);

    ~IrPrinter();

    virtual void Visit(IrBinaryOperator*) override final;

    virtual void Visit(IrCall*) override final;

    virtual void Visit(IrConditionalJump*) override final;

    virtual void Visit(IrConstant*) override final;

    virtual void Visit(IrJump*) override final;

    virtual void Visit(IrLabel*) override final;

    virtual void Visit(IrMemory*) override final;

    virtual void Visit(IrMove*) override final;

    virtual void Visit(IrName*) override final;

    virtual void Visit(IrSequence*) override final;

    virtual void Visit(IrTemporary*) override final;

private:
    void PrintHead(int headNodeNumber, const std::string& label);

    void PrintEdge(int headNodeNumber);

    void PrintLeaf(int headNodeNumber, const std::string& label, const std::string& name);

private:
    std::ofstream file_;
    int nodeNumber_;
};
