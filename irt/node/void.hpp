#pragma once

#include "statement.hpp"
#include <memory>

class Expression;

namespace Irt {

    class Void : public Statement {
    public:
        explicit Void(std::shared_ptr<Expression> expression);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::shared_ptr<Expression> expression_;
    };

}
