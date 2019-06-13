#include <irt/node/expression-list.hpp>

#include <cassert>

#include <irt/node/expression.hpp>

using namespace Irt;

std::unique_ptr<const ExpressionList> ExpressionList::Clone() const {
  ExpressionList* newList = new ExpressionList();
  for (auto it = expressions_.begin(); it != expressions_.end(); ++it) {
    newList->Add(std::move((*it)->Clone()));
  }
  return std::move(std::unique_ptr<const ExpressionList>(newList));
}
