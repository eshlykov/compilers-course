#pragma once

#include <unordered_map>
#include <vector>
#include "../../utils/ct.hpp"
#include "../basic-blocks/basic-blocks.hpp"
#include "statement-list.hpp"

namespace Ct {

class TraceScheduler {
 public:
  explicit TraceScheduler(BasicBlocks blocks) : theBlocks_(blocks) {
    for (std::shared_ptr<StatementListList> list = blocks.GetBlocks();
         list != nullptr; list = list->tail_) {
      table_[std::dynamic_pointer_cast<Label>(list->head_[0])->address_] =
          StatementList(list->head_);
    }
    statements_ = GetNext();
    table_.clear();
  }

  StatementList GetLast(StatementList block) {
    auto list = std::make_shared<StatementList>(std::move(block));
    while (list->tail_->tail_ != nullptr) {
      list = list->tail_;
    }
    return *list;
  }

  void Trace(std::vector<StatementPtr>& statements) {
    StatementList list(statements);
    Trace(list);
    statements = list.ToStatements();
  }

  void Trace(StatementList& list) {
    while (true) {
      auto label = std::dynamic_pointer_cast<Label>(list.head_);
      table_.erase(label->address_);
      StatementList last = GetLast(list);
      StatementPtr statement = last.tail_->head_;
      if (auto jump = std::dynamic_pointer_cast<Jump>(statement);
          jump != nullptr) {
        if (table_.count(jump->address_) == 1) {
          StatementList target = table_[jump->address_];
          last.tail_ = std::make_shared<StatementList>(target);
          list = target;
        } else {
          last.tail_->tail_ = std::make_shared<StatementList>(GetNext());
          return;
        }
      } else if (auto conditionalJump =
                     std::dynamic_pointer_cast<ConditionalJump>(statement);
                 conditionalJump != nullptr) {
        bool hasIfTrue = table_.count(conditionalJump->addressIf_) == 1;
        bool hasIfFalse = table_.count(conditionalJump->addressElse_) == 1;
        if (hasIfFalse) {
          StatementList ifFalse = table_[conditionalJump->addressElse_];
          last.tail_->tail_ = std::make_shared<StatementList>(ifFalse);
          list = ifFalse;
        } else if (hasIfTrue) {
          last.tail_->head_ = std::make_shared<ConditionalJump>(
              InverseLogicalOperator(conditionalJump->logicalOperator_),
              conditionalJump->expressionLeft_,
              conditionalJump->expressionRight_, conditionalJump->addressElse_,
              conditionalJump->addressIf_);
          StatementList ifTrue = table_[conditionalJump->addressIf_];
          last.tail_->tail_ = std::make_shared<StatementList>(ifTrue);
          list = ifTrue;
        } else {
          Address temp;
          last.tail_->head_ = std::make_shared<ConditionalJump>(
              conditionalJump->logicalOperator_,
              conditionalJump->expressionLeft_,
              conditionalJump->expressionRight_, conditionalJump->addressIf_,
              temp);
          last.tail_->tail_ = std::make_shared<StatementList>(
              std::make_shared<Label>(temp),
              std::make_shared<StatementList>(
                  std::make_shared<Jump>(conditionalJump->addressElse_),
                  std::make_shared<StatementList>(GetNext())));
          return;
        }
      } else {
        std::terminate();
      }
    }
  }

  StatementList GetNext() {
    if (theBlocks_.GetBlocks() == nullptr) {
      return StatementList{std::make_shared<Label>(theBlocks_.GetDone()),
                           nullptr};
    }

    StatementList list(theBlocks_.GetBlocks()->head_);
    auto label = std::dynamic_pointer_cast<Label>(list.head_);
    if (table_.count(label->address_) == 1) {
      Trace(list);
      return list;
    }

    theBlocks_.SetBlocks(theBlocks_.GetBlocks()->tail_);
    return GetNext();
  }

 private:
  StatementList statements_;
  BasicBlocks theBlocks_;
  std::unordered_map<Address, StatementList, AddressHasher> table_;
};

}  // namespace Ct
