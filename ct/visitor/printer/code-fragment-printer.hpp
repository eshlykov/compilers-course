#pragma once

#include "../../frame/code-fragment.hpp"
#include "printer.hpp"
#include <string>
#include <memory>

namespace Ct {

    void Print(const std::string& filename, std::shared_ptr<CodeFragment> codeFragment);

}
