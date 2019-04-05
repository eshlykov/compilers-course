#pragma once

#include "../node/statement.hpp"
#include "frame.hpp"

namespace Irt {

struct CodeFragment {
 public:
  CodeFragment();

 public:
  std::shared_ptr<Frame> frame_;
  std::shared_ptr<StatementSequence> body_;
  std::shared_ptr<CodeFragment> next_;
};

inline CodeFragment::CodeFragment()
    : frame_{nullptr}, body_{nullptr}, next_{nullptr} {}

}  // namespace Irt
