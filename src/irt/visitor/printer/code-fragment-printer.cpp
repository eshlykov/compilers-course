#include "code-fragment-printer.hpp"

namespace Irt {

    void Print(const std::string& filename, std::shared_ptr<CodeFragment> codeFragment) {
        Printer printer{filename};
        while (codeFragment != nullptr) {
            printer.Visit(codeFragment->body_.get());
            printer.Next();
            codeFragment = codeFragment->next_;
        }
    }

}
