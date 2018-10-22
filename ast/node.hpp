#pragma once

#include <memory>

class IVisitor;

class INode : public std::enable_shared_from_this<INode> {
public:
    virtual void Accept(std::shared_ptr<IVisitor>) = 0;
};
