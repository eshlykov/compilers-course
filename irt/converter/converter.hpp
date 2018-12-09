#pragma once

#include "../../utils/irt.hpp"
#include "../utils/address.hpp"
#include "../utils/register.hpp"
#include <memory>

namespace Irt {

    class Converter {
    public:
        virtual ~Converter() = default;

        virtual std::shared_ptr<Expression> ToExpression() const = 0;

        virtual std::shared_ptr<Statement> ToStatement() const = 0;

        virtual std::shared_ptr<Statement> ToConditionalJump(Address, Address) const = 0;
    };

}
