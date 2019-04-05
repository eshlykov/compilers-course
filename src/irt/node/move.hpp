#pragma once

#include <memory>
#include "statement.hpp"

namespace Irt {

class Expression;

class Move : public Statement {
 public:
  Move(std::shared_ptr<Expression> destination,
       std::shared_ptr<Expression> source);

  void Accept(Visitor* visitor) final;

 public:
  const std::shared_ptr<Expression> destination_;
  const std::shared_ptr<Expression> source_;
};

inline Move::Move(std::shared_ptr<Expression> destination,
                  std::shared_ptr<Expression> source)
    : destination_{destination}, source_{source} {
  assert(destination_ != nullptr);
  assert(source_ != nullptr);
}

inline void Move::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Irt
