#pragma once

#include <memory>
#include <vector>
#include "../../utils/ct.hpp"

namespace Ct {

class ExpressionCall : public Statement {
 public:
  ExpressionCall(std::shared_ptr<Call> call);

  void Accept(Visitor*) final {}

  std::vector<std::shared_ptr<Expression>> Kids() final;

  std::shared_ptr<Statement> Build(
      const std::vector<std::shared_ptr<Expression>>& kids) final;

 private:
  std::shared_ptr<Call> Call_;
};

inline ExpressionCall::ExpressionCall(std::shared_ptr<Call> call)
    : Call_(std::move(call)) {}

inline std::vector<std::shared_ptr<Expression>> ExpressionCall::Kids() {
  return Call_->Kids();
}

inline std::shared_ptr<Statement> ExpressionCall::Build(
    const std::vector<std::shared_ptr<Expression>>& kids) {
  return std::make_shared<Void>(Call_->Build(kids));
}

}  // namespace Ct
