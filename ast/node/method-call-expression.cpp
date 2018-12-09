#include "method-call-expression.hpp"

namespace Ast {

    MethodCallExpression::MethodCallExpression(Location location,
        std::unique_ptr<Expression> expression,
        const std::string& methodName,
        std::vector<std::unique_ptr<Expression>>& argumentsList) :
            expression_{std::move(expression)},
            methodName_{methodName},
            argumentsList_{std::move(argumentsList)} {
        SetLocation(location);
        assert(expression_ != nullptr);
    }

    void MethodCallExpression::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
