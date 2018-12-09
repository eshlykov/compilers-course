#pragma once

class IrJump;
class IrMove;

class IrVisitor {
public:
    virtual void Visit(IrJump*) = 0;
    virtual void Visit(IrMove*) = 0;
};
