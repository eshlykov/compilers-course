#pragma once

#include "expression.hpp"
#include "statement.hpp"
#include <memory>
#include <string>

namespace Ast {

    class AssignmentByIndexStatement : public Statement {
    public:
        AssignmentByIndexStatement(Location location,
            const std::string& array,
            std::unique_ptr<Expression> index,
            std::unique_ptr<Expression> expression);

        void Accept(Visitor* visitor) final;

    public:
        const std::string array_;
        const std::unique_ptr<Expression> index_;
        const std::unique_ptr<Expression> expression_;
    };

    inline AssignmentByIndexStatement::AssignmentByIndexStatement(Location location,
        const std::string& array,
        std::unique_ptr<Expression> index,
        std::unique_ptr<Expression> expression) :
        array_{array},
        index_{std::move(index)},
        expression_{std::move(expression)} {
        SetLocation(location);
        assert(index_ != nullptr);
        assert(expression_ != nullptr);
    }

    inline void AssignmentByIndexStatement::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
