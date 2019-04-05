#pragma once

#include <memory>
#include <string>
#include "../../utils/storage.hpp"
#include "expression.hpp"

namespace Ct {

class Temporary : public Expression {
 public:
  explicit Temporary(Storage storage);

  void Accept(Visitor *visitor) final;

  std::vector<std::shared_ptr<Expression>> Kids() final;

  std::shared_ptr<Expression> Build(
      const std::vector<std::shared_ptr<Expression>> &expressionList) final;

 public:
  const Storage storage_;
};

inline Temporary::Temporary(Storage storage) : storage_(storage) {}

inline void Temporary::Accept(Visitor *visitor) { visitor->Visit(this); }

inline std::vector<std::shared_ptr<Expression>> Temporary::Kids() { return {}; }

inline std::shared_ptr<Expression> Temporary::Build(
    const std::vector<std::shared_ptr<Expression>> &expressionList) {
  return std::make_shared<Temporary>(storage_);
}

}  // namespace Ct
