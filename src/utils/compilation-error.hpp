#pragma once

#include <ast/node/visitor-target.hpp>
#include <string>

class CompilationError {
 public:
  CompilationError(const Ast::Location& location, const std::string& message);
  const Ast::Location& GetLocation() const;
  const std::string& Message() const;
  std::string ToString() const;

  static const std::string redefinitionLocalVar_;
  static const std::string redefinitionClass_;
  static const std::string redefinitionMethid_;
  static const std::string differentTypesOfArguments_;
  static const std::string invalidPrintType_;
  static const std::string invalidConditionType_;
  static const std::string invalidIndexType_;
  static const std::string invalidLengthType_;
  static const std::string cyclicInheritance_;
  static const std::string parentClassNotExists_;
  static const std::string typeNotExists_;
  static const std::string undefinedVar_;
  // static const std::string METHOD_OVERLOADING;
  static const std::string classHasNoMethod_;
  static const std::string invalidCallerExpression_;
  static const std::string argCountsNotMatch_;
  static const std::string argTypesNotMatch_;
  static const std::string methodIsPrivate_;

 private:
  Ast::Location location_;
  std::string message_;
};
