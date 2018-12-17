#pragma once

#include "access.hpp"
#include "../node/memory.hpp"
#include "../node/temporary.hpp"
#include "../node/constant.hpp"
#include "../node/binary-operator.hpp"

namespace Irt {

    class InFrameAccess : public Access {
    public:
        explicit InFrameAccess(int offset);

        std::shared_ptr<Expression> GetData() const;

    private:
        int offset_;
    };

}
