#include "ast/expression.hpp"
#include "visitor/interpreter.hpp"

extern int yyparse();

int main() {
    std::shared_ptr<IVisitor> visitor{new Interpreter{}};
    std::shared_ptr<ExpressionAndExpression> expression{new ExpressionAndExpression{true}};
//    yyparse();
}
