#pragma once

#include "expression.hpp"
#include <memory>
#include <string>

namespace Irt {

    class Temporary : public Expression {
    public:
        explicit Temporary(const std::string& temporary);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::string temporary_;
    };

}
