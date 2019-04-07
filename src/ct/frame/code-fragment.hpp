#pragma once

#include "../../irt/frame/frame.hpp"
#include "../node/statement.hpp"
#include "frame.hpp"

namespace Ct {

struct CodeFragment {
 public:
  CodeFragment();

  CodeFragment(StatementPtr body, std::shared_ptr<Irt::Frame> frame);

 public:
  std::shared_ptr<Frame> frame_;
  StatementPtr body_;
  std::shared_ptr<CodeFragment> next_;
};

inline CodeFragment::CodeFragment()
    : frame_{nullptr}, body_{nullptr}, next_{nullptr} {}

CodeFragment::CodeFragment(StatementPtr body, std::shared_ptr<Irt::Frame> frame)
    : body_{std::move(body)}, frame_{frame} {

}

}  // namespace Ct
