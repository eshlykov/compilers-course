#include "expression.hpp"

void Expression::SetType(const std::variant<TypeKind, std::string>& type) {
    type_ = type;
}

std::variant<TypeKind, std::string> Expression::GetType() const {
    return type_;
}
