#include "code-fragment.hpp"

namespace Irt {

    CodeFragment::CodeFragment(std::shared_ptr<Frame> frame,
        std::shared_ptr<Statement> body) :
            frame_{frame},
            body_{body} {
    }

}
