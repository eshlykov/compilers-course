#pragma once

#include "../node/statement.hpp"
#include "frame.hpp"

namespace Irt {

    class CodeFragment {
    public:
        CodeFragment(const std::shared_ptr<Frame>, const std::shared_ptr<Statement>);

    private:
        const std::shared_ptr<Frame> frame_;
        const std::shared_ptr<Statement> body_;
    };

}
