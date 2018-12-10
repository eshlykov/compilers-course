#pragma once

#include "expression.hpp"
#include <memory>
#include <string>

namespace Irt {

    class Temporary : public Expression {
    public:
        explicit Temporary(Storage storage);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const Storage storage_;
    };

}
