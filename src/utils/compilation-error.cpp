#include <sstream>
#include <utils/compilation-error.hpp>

using namespace Ast;

const std::string CompilationError::redefinitionLocalVar_ =
    "Local variable redefined";
const std::string CompilationError::redefinitionClass_ = "Class redefined";
const std::string CompilationError::redefinitionMethid_ = "Method redefined";
const std::string CompilationError::differentTypesOfArguments_ =
    "Different types of left and right part";
const std::string CompilationError::invalidPrintType_ =
    "Can't print not Int expression_";
const std::string CompilationError::invalidConditionType_ =
    "Condition must have boolean arguments";
const std::string CompilationError::invalidIndexType_ =
    "Index should have integer type";
const std::string CompilationError::invalidLengthType_ =
    "Array length must have integer type";
const std::string CompilationError::cyclicInheritance_ = "Cyclic inheritance";
const std::string CompilationError::parentClassNotExists_ =
    "Parent class does not exist";
const std::string CompilationError::typeNotExists_ = "Type does not exist";
const std::string CompilationError::undefinedVar_ = "Variable was not defined";
// const std::string CCompilationError::METHOD_OVERLOADING = "Method is being
// overloaded";
const std::string CompilationError::classHasNoMethod_ =
    "Method is not defined in caller-class";
const std::string CompilationError::invalidCallerExpression_ =
    "Invalid caller expression_";
const std::string CompilationError::argCountsNotMatch_ =
    "Arguments numbers do not match";
const std::string CompilationError::argTypesNotMatch_ =
    "Argument type does not match";
const std::string CompilationError::methodIsPrivate_ =
    "Calling a private method from a different class";

CompilationError::CompilationError(const Location& location,
                                   const std::string& message)
    : location_(location), message_(message) {}

const Location& CompilationError::GetLocation() const { return location_; }

const std::string& CompilationError::Message() const { return message_; }

std::string CompilationError::ToString() const {
  std::stringstream sstream;
  sstream << location_.firstLine_ << ':' << location_.firstColumn_ << ": "
          << message_;
  return sstream.str();
}
