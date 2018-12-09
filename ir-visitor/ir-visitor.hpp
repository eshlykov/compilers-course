#pragma once

class IrConditionalJump;
class IrConstant;
class IrJump;
class IrName;
class IrMove;
class IrTemporary;
class IrBinaryOperator;

class IrVisitor {
public:
    virtual void Visit(IrConstant*) = 0;
    virtual void Visit(IrConditionalJump*) = 0;
    virtual void Visit(IrJump*) = 0;
    virtual void Visit(IrMove*) = 0;
    virtual void Visit(IrName*) = 0;
    virtual void Visit(IrTemporary*) = 0;
    virtual void Visit(IrBinaryOperator*) = 0;
};
