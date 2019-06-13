#pragma once

#include <string>

namespace Ast {

class NodeNames {
 public:
  static const std::string accessModPrivate_;
  static const std::string accessModePublic_;
  static const std::string classDecl_;
  static const std::string classDeclList_;
  static const std::string expBinary_;
  static const std::string expBracket_;
  static const std::string expId_;
  static const std::string expLength_;
  static const std::string expList_;
  static const std::string expLogic_;
  static const std::string expMethod_;
  static const std::string expNegate_;
  static const std::string expNewArray_;
  static const std::string expNewId_;
  static const std::string expNumber_;
  static const std::string expThis_;
  static const std::string mainClass_;
  static const std::string methArg_;
  static const std::string methAgrList_;
  static const std::string methDecl_;
  static const std::string methDeclList_;
  static const std::string program_;
  static const std::string statAssignId_;
  static const std::string statAssignIdWithIndex_;
  static const std::string statBraces_;
  static const std::string statConditional_;
  static const std::string statList_;
  static const std::string statPrint_;
  static const std::string statWhileLoop_;
  static const std::string typeModeBool_;
  static const std::string typeModeId_;
  static const std::string typeModInt_;
  static const std::string typeModIntArray_;
  static const std::string varDecl_;
  static const std::string varDeclList_;
};

}  // namespace Ast
