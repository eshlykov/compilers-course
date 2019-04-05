#pragma once

#include "node.hpp"
#include <string>
#include <variant>

namespace Ast {

    class Expression : public Node {
    public:
        void SetType(const std::variant<TypeKind, std::string>& type);

        std::variant<TypeKind, std::string> GetType() const;

    private:
        std::variant<TypeKind, std::string> type_;
    };

    inline void Expression::SetType(const std::variant<TypeKind, std::string>& type) {
        type_ = type;
    }

    inline std::variant<TypeKind, std::string> Expression::GetType() const {
        return type_;
    }

}
