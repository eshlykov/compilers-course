#pragma once

#include <memory>
#include <vector>
#include "../../utils/ct.hpp"

namespace Ct {

class ExpressionCall : public Statement {
 public:
  explicit ExpressionCall(CallPtr call);

  void Accept(Visitor*) final {}

  std::vector<ExpressionPtr> Kids() final;

  StatementPtr Build(const std::vector<ExpressionPtr>& kids) final;

 private:
  CallPtr call_;
};

inline ExpressionCall::ExpressionCall(CallPtr call) : call_(std::move(call)) {}

inline std::vector<ExpressionPtr> ExpressionCall::Kids() {
  return call_->Kids();
}

inline StatementPtr ExpressionCall::Build(
    const std::vector<ExpressionPtr>& kids) {
  return std::make_shared<Void>(call_->Build(kids));
}

}  // namespace Ct
