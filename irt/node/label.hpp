#pragma once

#include "statement.hpp"
#include <memory>
#include <string>

namespace Irt {

    class Label : public Statement {
    public:
        explicit Label(const std::string& label);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::string label_;
    };

}
