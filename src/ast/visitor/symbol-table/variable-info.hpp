#pragma once

#include <optional>
#include <string>
#include <variant>
#include "../../../utils/ast.hpp"

namespace Ast {

struct VariableInfo {
  std::variant<TypeKind, std::string> type_;
  size_t offset_;
};

}  // namespace Ast
