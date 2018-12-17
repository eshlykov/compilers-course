#include "code-fragment-printer.hpp"

namespace Irt {

    void Print(const std::string& filename, std::shared_ptr<CodeFragment> codeFragment) {
        Printer printer{filename};
        auto body = std::make_shared<ExpressionSequence>(
            codeFragment->body_,
            std::make_shared<Constant>(0)
        );
        printer.Visit(body.get());
        codeFragment = codeFragment->next_;
    }

}
