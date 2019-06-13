#include <utility>

#pragma once

#include <cg/node/visitor-target.hpp>
#include <irt/node/expression.hpp>
#include <string>
#include <vector>

namespace Cg {

class Command : public VisitorTarget {};

// Expressions = arithmetic operations results, stores result to register
class Expression : public Command {};

class NullExpression : public Expression {
 public:
  NullExpression() = default;

  ~NullExpression() override = default;

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }
};

// Virtual expression_ resonsible for some register (temp node on the ir-level)
class TempExpression : public Expression {
 public:
  explicit TempExpression(std::string name) : name_(std::move(name)) {}
  ~TempExpression() override = default;

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  const std::string& Name() const { return name_; }

 private:
  std::string name_;
};

class AddCommand : public Expression {
 public:
  AddCommand(const Expression* leftOperand, const Expression* rightOperand)
      : leftOperand_(leftOperand), rightOperand_(rightOperand) {}
  ~AddCommand() override = default;

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  const Expression* LeftOperand() const { return leftOperand_; }
  const Expression* RightOperand() const { return rightOperand_; }

 private:
  const Expression* leftOperand_;
  const Expression* rightOperand_;
};

class AddConstCommand : public Expression {
 public:
  AddConstCommand(const Expression* expression, const int constant)
      : expression_(expression), constant_(constant) {}
  ~AddConstCommand() override = default;

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  const Expression* GetExpression() const { return expression_; }
  int Constant() const { return constant_; }

 private:
  const Expression* expression_;
  const int constant_;
};

class SubCommand : public Expression {
 public:
  SubCommand(const Expression* leftOperand, const Expression* rightOperand)
      : leftOperand_(leftOperand), rightOperand_(rightOperand) {}
  ~SubCommand() override = default;

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  const Expression* LeftOperand() const { return leftOperand_; }
  const Expression* RightOperand() const { return rightOperand_; }

 private:
  const Expression* leftOperand_;
  const Expression* rightOperand_;
};

class SubConstCommand : public Expression {
 public:
  SubConstCommand(const Expression* expression, const int constant)
      : expression_(expression), constant_(constant) {}
  ~SubConstCommand() override = default;

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  const Expression* GetExpression() const { return expression_; }
  int Constant() const { return constant_; }

 private:
  const Expression* expression_;
  const int constant_;
};

class MultCommand : public Expression {
 public:
  MultCommand(const Expression* leftOperand, const Expression* rightOperand)
      : leftOperand_(leftOperand), rightOperand_(rightOperand) {}
  ~MultCommand() override = default;

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  const Expression* LeftOperand() const { return leftOperand_; }
  const Expression* RightOperand() const { return rightOperand_; }

 private:
  const Expression* leftOperand_;
  const Expression* rightOperand_;
};

class DivCommand : public Expression {
 public:
  DivCommand(const Expression* leftOperand, const Expression* rightOperand)
      : leftOperand_(leftOperand), rightOperand_(rightOperand) {}
  ~DivCommand() override = default;

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  const Expression* LeftOperand() const { return leftOperand_; }
  const Expression* RightOperand() const { return rightOperand_; }

 private:
  const Expression* leftOperand_;
  const Expression* rightOperand_;
};

// Get's value from memory: M[src + offset]
class LoadCommand : public Expression {
 public:
  LoadCommand(const Expression* source, const int offset)
      : source_(source), offset_(offset) {}

  ~LoadCommand() override = default;

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  const Expression* Source() const { return source_; }
  int Offset() const { return offset_; }

 private:
  const Expression* source_;
  const int offset_;
};

// Statements - operations without storing result
class Statement : public Command {};

// Memory Statements - stores result to memory cell
class MemoryStatement : public Statement {};

// M[dst + offset] = src
class StoreCommand : public MemoryStatement {
 public:
  StoreCommand(const Expression* destination, const int offset,
               const Expression* source)
      : destination_(destination), offset_(offset), source_(source) {}

  ~StoreCommand() override = default;

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  const Expression* Destination() const { return destination_; }
  int Offset() const { return offset_; }
  const Expression* Source() const { return source_; }

 private:
  const Expression* destination_;
  const int offset_;
  const Expression* source_;
};

// dst = src
class MoveRegisterCommand : public Statement {
 public:
  MoveRegisterCommand(const TempExpression* destination,
                      const Expression* source)
      : destination_(destination), source_(source) {}

  ~MoveRegisterCommand() override = default;

  const TempExpression* Destination() const { return destination_; }
  const Expression* Source() const { return source_; }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  const TempExpression* destination_;
  const Expression* source_;
};

class LabelDeclarationCommand : public Command {
 public:
  explicit LabelDeclarationCommand(std::string name) : name_(std::move(name)) {}
  ~LabelDeclarationCommand() override = default;

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  const std::string& Name() const { return name_; }

 private:
  std::string name_;
};

class CallFunctionCommand : public Expression {
 public:
  CallFunctionCommand(std::string function,
                      std::vector<const Expression*> arguments)
      : function_(std::move(function)), arguments_(std::move(arguments)) {}

  ~CallFunctionCommand() override = default;

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  const std::string& Function() const { return function_; }
  const std::vector<const Cg::Expression*>& Arguments() const {
    return arguments_;
  }

 private:
  const std::string function_;
  const std::vector<const Cg::Expression*> arguments_;
};

class JumpCommand : public Statement {
 public:
  explicit JumpCommand(std::string labelName)
      : labelName_(std::move(labelName)) {}
  ~JumpCommand() override = default;

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  const std::string& LabelName() const { return labelName_; }

 private:
  std::string labelName_;
};

class ConditionalJumpCommand : public Statement {
 public:
  ConditionalJumpCommand(const Expression* leftPart,
                         const Expression* rightPart,
                         Irt::LogicOperatorTypes cmp,
                         std::string positiveLabelName,
                         std::string negativeLabelName)
      : leftPart_(leftPart),
        rightPart_(rightPart),
        cmp_(cmp),
        positiveLabelName_(std::move(positiveLabelName)),
        negativeLabelName_(std::move(negativeLabelName)) {}
  ~ConditionalJumpCommand() override = default;

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  const Expression* LeftPart() const { return leftPart_; }
  const Expression* RightPart() const { return rightPart_; }
  Irt::LogicOperatorTypes Cmp() const { return cmp_; }
  const std::string& PositiveLabelName() const { return positiveLabelName_; }
  const std::string& NegativeLabelName() const { return negativeLabelName_; }

 private:
  const Expression* leftPart_;
  const Expression* rightPart_;
  Irt::LogicOperatorTypes cmp_;
  std::string positiveLabelName_;
  std::string negativeLabelName_;
};

class ExpStatementCommand : public Statement {
 public:
  explicit ExpStatementCommand(const Expression* expression)
      : expression_(expression) {}
  ~ExpStatementCommand() override = default;

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }
  const Expression* GetExpression() const { return expression_; }

 private:
  const Expression* expression_;
};

}  // namespace Cg
