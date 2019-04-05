#pragma once

#include <memory>
#include <vector>
#include "../../utils/ct.hpp"

namespace Ct {

class MoveCall : public Statement {
 public:
  MoveCall(TemporaryPtr destination, CallPtr source);

  void Accept(Visitor*) final {}

  std::vector<ExpressionPtr> Kids() final;

  StatementPtr Build(const std::vector<ExpressionPtr>& kids) final;

 private:
  TemporaryPtr destination_;
  CallPtr source_;
};

inline MoveCall::MoveCall(TemporaryPtr destination, CallPtr source)
    : destination_(std::move(destination)), source_(std::move(source)) {}

inline std::vector<ExpressionPtr> MoveCall::Kids() { return source_->Kids(); }

inline StatementPtr MoveCall::Build(const std::vector<ExpressionPtr>& kids) {
  return std::make_shared<Move>(destination_, source_->Build(kids));
}

}  // namespace Ct
