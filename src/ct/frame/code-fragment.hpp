#pragma once

#include "../../irt/frame/frame.hpp"
#include "../node/statement-sequence.hpp"
#include "frame.hpp"

namespace Ct {

struct CodeFragment {
 public:
  CodeFragment();

  CodeFragment(const std::shared_ptr<Statement>& body,
               const std::shared_ptr<Irt::Frame>& frame);

 public:
  std::shared_ptr<Frame> frame_;
  std::shared_ptr<StatementSequence> body_;
  std::shared_ptr<CodeFragment> next_;
};

inline CodeFragment::CodeFragment()
    : frame_{nullptr}, body_{nullptr}, next_{nullptr} {}

inline CodeFragment::CodeFragment(const std::shared_ptr<Statement>& body,
                                  const std::shared_ptr<Irt::Frame>& frame)
    : body_{std::dynamic_pointer_cast<StatementSequence>(body)},
      frame_{std::make_shared<Frame>(frame)} {
  assert(body);
}

}  // namespace Ct
