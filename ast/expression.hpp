#pragma once

#include "node.hpp"
#include <string>
#include <variant>

class Expression : public Node {
public:
    std::variant<TypeKind, std::string> type_;
};
