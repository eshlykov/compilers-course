#pragma once

#include "../node/expression.hpp"
#include <memory>

namespace Ct {

    class Access {
    public:
        virtual ~Access() = default;

        virtual std::shared_ptr<Expression> GetData() const = 0;
    };

}
