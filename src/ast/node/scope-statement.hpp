#pragma once

#include "statement.hpp"
#include <memory>
#include <vector>

namespace Ast {

    class ScopeStatement : public Statement {
    public:
        explicit ScopeStatement(Location location,
            std::vector<std::unique_ptr<Statement>>& statements);


        void Accept(Visitor* visitor) final;

    public:
        const std::vector<std::unique_ptr<Statement>> statements_;
    };

    inline ScopeStatement::ScopeStatement(Location location,
        std::vector<std::unique_ptr<Statement>>& statements) :
        statements_{std::move(statements)} {
        SetLocation(location);
    }

    inline void ScopeStatement::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
