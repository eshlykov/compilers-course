#pragma once

#include "../../../utils/irt.hpp"
#include "../visitor.hpp"
#include <fstream>
#include <string>

class Printer : public Visitor {
public:
    explicit Printer(const std::string& filename);

    ~Printer();

    virtual void Visit(BinaryOperator*) override final;

    virtual void Visit(Call*) override final;

    virtual void Visit(Constant*) override final;

    virtual void Visit(Jump*) override final;

    virtual void Visit(Label*) override final;

    virtual void Visit(Memory*) override final;

    virtual void Visit(Move*) override final;

    virtual void Visit(Name*) override final;

    virtual void Visit(Sequence*) override final;

    virtual void Visit(Temporary*) override final;

private:
    void PrintHead(int headNodeNumber, const std::string& label);

    void PrintEdge(int headNodeNumber);

    void PrintLeaf(int headNodeNumber, const std::string& label, const std::string& name);

private:
    std::ofstream file_;
    int nodeNumber_;
};
