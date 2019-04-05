#pragma once

#include <memory>
#include "expression.hpp"

namespace Ast {

class IndexExpression : public Expression {
 public:
  IndexExpression(Location location, std::unique_ptr<Expression> lhs,
                  std::unique_ptr<Expression> rhs);

  void Accept(Visitor* visitor) final;

 public:
  const std::unique_ptr<Expression> lhs_;
  const std::unique_ptr<Expression> rhs_;
};

inline IndexExpression::IndexExpression(Location location,
                                        std::unique_ptr<Expression> lhs,
                                        std::unique_ptr<Expression> rhs)
    : lhs_{std::move(lhs)}, rhs_{std::move(rhs)} {
  SetLocation(location);
  assert(lhs_ != nullptr);
  assert(rhs_ != nullptr);
}

inline void IndexExpression::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Ast
