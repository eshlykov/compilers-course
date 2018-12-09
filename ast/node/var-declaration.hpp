#pragma once

#include "node.hpp"
#include "type.hpp"
#include <memory>

namespace Ast {

    class VarDeclaration : public Node {
    public:
        VarDeclaration(Location location,
            std::unique_ptr<Type> type,
            const std::string& name);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::unique_ptr<Type> type_;
        const std::string name_;
    };

}
