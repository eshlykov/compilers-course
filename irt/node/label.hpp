#pragma once

#include "statement.hpp"
#include <memory>
#include <string>

namespace Irt {

    class Label : public Statement {
    public:
        explicit Label(const Address& label);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const Address label_;
    };

}
