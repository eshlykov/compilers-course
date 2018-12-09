#pragma once

class IrMove;

class IrVisitor {
public:
    virtual void Visit(IrMove*) = 0;
};
