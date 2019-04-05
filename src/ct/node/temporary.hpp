#pragma once

#include <memory>
#include <string>
#include "../utils/storage.hpp"
#include "expression.hpp"

namespace Ct {

class Temporary : public Expression {
 public:
  explicit Temporary(Storage storage);

  virtual void Accept(Visitor* visitor) override final;

  virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

  virtual std::shared_ptr<Expression> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList)
      override final;

 public:
  const Storage storage_;
};

}  // namespace Ct
