#pragma once

#include <memory>

class Expression;
class Statement;

namespace Irt {

    class Converter {
    public:
        virtual ~Converter() = default;

        virtual std::shared_ptr<Expression> ToExpression() const = 0;

        virtual std::shared_ptr<Statement> ToStatement() const = 0;

        virtual std::shared_ptr<Statement> ToConditionalJump() const = 0;
    };

}
