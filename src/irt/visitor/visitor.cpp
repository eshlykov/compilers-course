#include <irt/node/expression.hpp>
#include <irt/visitor/visitor.hpp>

using namespace Irt;

int Visitor::GenerateNodeNextIndex(const std::string &nodeType) {
  int result = 0;
  auto insertResult =
      nodeTypeLastUsedIndex_.insert(std::make_pair(nodeType, result));
  if (!insertResult.second) {
    result = ++insertResult.first->second;
  }
  return result;
}

std::string Visitor::GenerateNodeName(const std::string &nodeTypeName) {
  return nodeTypeName + std::to_string(GenerateNodeNextIndex(nodeTypeName));
}

std::string Visitor::OperatorName(const OperatorTypes &type) const {
  std::string result;
  switch (type) {
    case OperatorTypes::Plus:
      result = "Plus";
      break;
    case OperatorTypes::Minus:
      result = "Minus";
      break;
    case OperatorTypes::Times:
      result = "Times";
      break;
    case OperatorTypes::Div:
      result = "Div";
      break;
    case OperatorTypes::Mod:
      result = "Mod";
      break;
    case OperatorTypes::And:
      result = "And";
      break;
    case OperatorTypes::Or:
      result = "Or";
      break;
  }
  return result;
}

std::string Visitor::OperatorName(const LogicOperatorTypes &type) const {
  std::string result;
  switch (type) {
    case LogicOperatorTypes::Equal:
      result = "EQ";
      break;
    case LogicOperatorTypes::NotEqual:
      result = "NE";
      break;
    case LogicOperatorTypes::Less:
      result = "LT";
      break;
    case LogicOperatorTypes::Greater:
      result = "GT";
      break;
    case LogicOperatorTypes::LessEqual:
      result = "LE";
      break;
    case LogicOperatorTypes::GreaterEqual:
      result = "GE";
      break;
      //    case LogicOperatorTypes::LOT_ULT:
      //      result = "ULT";
      //      break;
      //    case LogicOperatorTypes::LOT_ULE:
      //      result = "ULE";
      //      break;
      //    case LogicOperatorTypes::LOT_UGT:
      //      result = "UGT";
      //      break;
      //    case LogicOperatorTypes::LOT_UGE:
      //      result = "UGE";
      //      break;
  }
  return result;
}

std::string Visitor::OperatorChar(const OperatorTypes &type) const {
  std::string result;
  switch (type) {
    case OperatorTypes::Plus:
      result = "+";
      break;
    case OperatorTypes::Minus:
      result = "-";
      break;
    case OperatorTypes::Times:
      result = "*";
      break;
    case OperatorTypes::Div:
      result = "/";
      break;
    case OperatorTypes::Mod:
      result = "%";
      break;
    case OperatorTypes::And:
      result = "&&";
      break;
    case OperatorTypes::Or:
      result = "||";
      break;
  }
  return result;
}

void Visitor::OnNodeEnter(const std::string &nodeName) {
  if (verbose_) {
    std::cout << margin_ << nodeEnterMarker_ << nodeName << std::endl;
    // margin.push_back( '\t' );
    margin_.append("  ");
  }
}

void Visitor::OnNodeExit(const std::string &nodeName) {
  if (verbose_) {
    margin_.erase(margin_.size() - 2);
    // margin.pop_back();
    std::cout << margin_ << nodeExitMarker_ << nodeName << std::endl;
  }
}
