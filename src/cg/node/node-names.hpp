#pragma once

#include <string>

namespace Cg {

class NodeNames {
 public:
  static const std::string cjump_;
  static const std::string jump_;
  static const std::string call_;
  static const std::string label_;
  static const std::string moveRegister_;
  static const std::string temp_;
  static const std::string add_;
  static const std::string addConst_;
  static const std::string sub_;
  static const std::string subConst_;
  static const std::string mult_;
  static const std::string div_;
  static const std::string load_;
  static const std::string store_;
  static const std::string moveCommand_;
  static const std::string nullExp_;
  static const std::string expStat_;
};

}  // namespace Cg
