#pragma once

#include "node.hpp"
#include <memory>
#include <vector>

namespace Ct {

	class Expression;

    class Statement : public Node {
    public:
        virtual std::vector<std::shared_ptr<Expression>> Kids() = 0;

        virtual std::shared_ptr<Statement> Build(const std::vector<std::shared_ptr<Expression>>& expressionList) = 0;
    };

}
