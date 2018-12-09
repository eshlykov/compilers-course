#pragma once

class IrBinaryOperator;
class IrCall;
class IrConditionalJump;
class IrConstant;
class IrJump;
class IrLabel;
class IrMemory;
class IrMove;
class IrName;
class IrSequence;
class IrTemporary;

class IrVisitor {
public:
    virtual void Visit(IrBinaryOperator*) = 0;
    virtual void Visit(IrCall*) = 0;
    virtual void Visit(IrConditionalJump*) = 0;
    virtual void Visit(IrConstant*) = 0;
    virtual void Visit(IrJump*) = 0;
    virtual void Visit(IrLabel*) = 0;
    virtual void Visit(IrMemory*) = 0;
    virtual void Visit(IrMove*) = 0;
    virtual void Visit(IrName*) = 0;
    virtual void Visit(IrSequence*) = 0;
    virtual void Visit(IrTemporary*) = 0;
};
