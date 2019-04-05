#pragma once

#include <memory>
#include <vector>
#include "../../utils/ct.hpp"

namespace Ct {

class MoveCall : public Statement {
 public:
  MoveCall(std::shared_ptr<Temporary> destination,
           std::shared_ptr<Call> source);

  void Accept(Visitor*) final {}

  std::vector<std::shared_ptr<Expression>> Kids() final;

  std::shared_ptr<Statement> Build(
      const std::vector<std::shared_ptr<Expression>>& kids) final;

 private:
  std::shared_ptr<Temporary> Destination_;
  std::shared_ptr<Call> Source_;
};

inline MoveCall::MoveCall(std::shared_ptr<Temporary> destination,
                          std::shared_ptr<Call> source)
    : Destination_(std::move(destination)), Source_(std::move(source)) {}

inline std::vector<std::shared_ptr<Expression>> MoveCall::Kids() {
  return Source_->Kids();
}

inline std::shared_ptr<Statement> MoveCall::Build(
    const std::vector<std::shared_ptr<Expression>>& kids) {
  return std::make_shared<Move>(Destination_, Source_->Build(kids));
}

}  // namespace Ct
