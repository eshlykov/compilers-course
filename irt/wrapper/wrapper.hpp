#pragma once

#include "../../utils/irt.hpp"
#include "../utils/address.hpp"
#include "../utils/register.hpp"
#include <memory>

namespace Irt {

    class Wrapper {
    public:
        virtual ~Wrapper() = default;

        virtual std::shared_ptr<Expression> ToRValue() const = 0;

        virtual std::shared_ptr<Statement> ToCondition(Address ifTrue, Address ifFalse) const = 0;
    };

}
