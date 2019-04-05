#pragma once

#include <memory>
#include <string>
#include "../../frame/code-fragment.hpp"
#include "printer.hpp"

namespace Ct {

void Print(const std::string& filename,
           std::shared_ptr<CodeFragment> codeFragment);

}
