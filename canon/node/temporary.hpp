#pragma once

#include "../utils/storage.hpp"
#include "expression.hpp"
#include <memory>
#include <string>

namespace Ct {

    class Temporary : public Expression {
    public:
        explicit Temporary(Storage storage);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const Storage storage_;
    };

}
