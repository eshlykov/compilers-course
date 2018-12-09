#pragma once

#include <memory>

class Expression;
class Statement;

namespace Irt {

    class Converter {
    public:
        virtual ~Converter() = default;

        virtual std::shared_ptr<const Expression> ToExpression() const = 0;

        virtual std::shared_ptr<const Statement> ToStatement() const = 0;

        virtual std::shared_ptr<const Statement> ToJump() const = 0;
    };

}
