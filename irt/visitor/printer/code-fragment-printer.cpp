#include "code-fragment-printer.hpp"

#include <iostream>

namespace Irt {

    void Print(const std::string& filename, std::shared_ptr<CodeFragment> codeFragment) {
        Printer printer{filename};
        while (codeFragment != nullptr) {
            auto body = std::make_shared<ExpressionSequence>(
                codeFragment->body_,
                std::make_shared<Constant>(0)
            );
            std::cout << "!!!" << std::endl;
            printer.Visit(body.get());
            printer.Next();
            codeFragment = codeFragment->next_;
        }
    }

}
