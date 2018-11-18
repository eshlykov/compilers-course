#pragma once

#include "../../ast.hpp"
#include <string>
#include <variant>

class VariableInfo {
public:
    std::variant<TypeKind, std::string> type_;
};
