#pragma once

#include <string>

namespace Irt {

class NodeNames {
 public:
  static const std::string expBinary_;
  static const std::string expCall_;
  static const std::string expConst_;
  static const std::string expEseq_;
  static const std::string expMem_;
  static const std::string expName_;
  static const std::string expTemp_;

  static const std::string statExp_;
  static const std::string statCJump_;
  static const std::string statJump_;
  static const std::string statLabel_;
  static const std::string statMove_;
  static const std::string statSeq_;

  static const std::string listExp_;
  static const std::string listStat_;
};

}  // namespace Irt
