#include "code-fragment-printer.hpp"

namespace Irt {

    void Print(const std::string& filename, std::shared_ptr<CodeFragment> codeFragment) {
        Printer printer{filename};
        while (codeFragment != nullptr) {
            auto body = std::make_shared<ExpressionSequence>(
                codeFragment->body_,
                std::make_shared<Constant>(0)
            );
            printer.Visit(body.get());
            printer.Next();
            codeFragment = codeFragment->next_;
        }
    }

}
