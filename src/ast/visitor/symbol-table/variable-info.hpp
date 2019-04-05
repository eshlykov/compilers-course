#pragma once

#include "../../../utils/ast.hpp"
#include <optional>
#include <string>
#include <variant>

namespace Ast {

    struct VariableInfo {
        std::variant<TypeKind, std::string> type_;
        int offset_;
    };

}