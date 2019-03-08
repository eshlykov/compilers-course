#pragma once

#include "../utils/address.hpp"
#include "expression.hpp"
#include <memory>

namespace Ct {

    class Name : public Expression {
    public:
        explicit Name(const Address& address);

        virtual void Accept(Visitor* visitor) override final;

        virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

        virtual std::shared_ptr<Expression> Build(
            const std::vector<std::shared_ptr<Expression>>& expressionList) override final;

    public:
        const Address address_;
    };

}
