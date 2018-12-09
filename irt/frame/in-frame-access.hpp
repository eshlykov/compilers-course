#pragma once

#include "access.hpp"

namespace Irt {

    class InFrameAccess : public Access {
    public:
        explicit InFrameAccess(int offset);

    private:
        int offset_;
    };

}
