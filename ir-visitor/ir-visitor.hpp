#pragma once

class IrConditionalJump;
class IrJump;
class IrMove;
class IrName;
class IrConstant;
class IrTemporary;

class IrVisitor {
public:
    virtual void Visit(IrConditionalJump*) = 0;
    virtual void Visit(IrJump*) = 0;
    virtual void Visit(IrMove*) = 0;
    virtual void Visit(IrName*) = 0;
    virtual void Visit(IrConstant*) = 0;
    virtual void Visit(IrTemporary*) = 0;
};
