#pragma once

#include "../../utils/ast.hpp"
#include <string>
#include <variant>

struct VariableInfo {
    std::variant<TypeKind, std::string> type_;
};
