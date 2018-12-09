#pragma once

#include "../../utils/irt.hpp"
#include <memory>

namespace Irt {

    class Converter {
    public:
        virtual ~Converter() = default;

        virtual std::shared_ptr<Expression> ToExpression() const = 0;

        virtual std::shared_ptr<Statement> ToStatement() const = 0;

        virtual std::shared_ptr<Statement> ToConditionalJump(std::shared_ptr<Label>,
            std::shared_ptr<Label>) const = 0;
    };

}
