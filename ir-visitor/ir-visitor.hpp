#pragma once

class IrConditionalJump;
class IrJump;
class IrMove;

class IrVisitor {
public:
    virtual void Visit(IrConditionalJump*) = 0;
    virtual void Visit(IrJump*) = 0;
    virtual void Visit(IrMove*) = 0;
};
