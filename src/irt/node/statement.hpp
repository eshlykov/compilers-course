#pragma once

#include <irt/node/visitor-target.hpp>
#include <memory>
#include <utils/address.hpp>

namespace Irt {

class Statement : public IVisitorTarget {
 public:
  virtual ~Statement();
  virtual std::unique_ptr<const Statement> Clone() const = 0;
};

enum class LogicOperatorTypes : char {
  Equal,
  NotEqual,
  Less,
  Greater,
  LessEqual,
  GreaterEqual,
  //  LOT_ULT,
  //  LOT_ULE,
  //  LOT_UGT,
  //  LOT_UGE
};

//-----------------------------------------------------------------------------------------------//
class Expression;

class MoveStatement : public Statement {
 public:
  MoveStatement(const Expression* destination, const Expression* source);
  MoveStatement(std::unique_ptr<const Expression> destination,
                std::unique_ptr<const Expression> source);
  ~MoveStatement();

  const Expression* Destination() const { return destination_.get(); }
  const Expression* Source() const { return source_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  std::unique_ptr<const Statement> Clone() const override;

 private:
  std::unique_ptr<const Expression> destination_;
  std::unique_ptr<const Expression> source_;
};

//-----------------------------------------------------------------------------------------------//

class ExpStatement : public Statement {
 public:
  explicit ExpStatement(const Expression* expression);
  explicit ExpStatement(std::unique_ptr<const Expression> expression);
  ~ExpStatement();

  const Expression* GetExpression() const { return expression_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  std::unique_ptr<const Statement> Clone() const override;

 private:
  std::unique_ptr<const Expression> expression_;
};

//-----------------------------------------------------------------------------------------------//

class JumpStatement : public Statement {
 public:
  JumpStatement(Address target);
  ~JumpStatement();

  Address Target() const { return target_; }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  std::unique_ptr<const Statement> Clone() const override;

 private:
  Address target_;
};

//-----------------------------------------------------------------------------------------------//

class JumpConditionalStatement : public Statement {
 public:
  JumpConditionalStatement(LogicOperatorTypes operation, const Expression* left,
                           const Expression* right, Address labelTrue,
                           Address labelFalse);
  JumpConditionalStatement(LogicOperatorTypes operation,
                           std::unique_ptr<const Expression> left,
                           std::unique_ptr<const Expression> right,
                           Address labelTrue, Address labelFalse);
  ~JumpConditionalStatement();

  const Expression* LeftOperand() const { return leftOperand_.get(); }
  const Expression* RightOperand() const { return rightOperand_.get(); }
  Address TrueLabel() const { return labelTrue_; }
  Address FalseLabel() const { return labelFalse_; }
  LogicOperatorTypes Operation() const { return operation_; }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  std::unique_ptr<const Statement> Clone() const override;

 private:
  std::unique_ptr<const Expression> leftOperand_;
  std::unique_ptr<const Expression> rightOperand_;
  Address labelTrue_;
  Address labelFalse_;
  LogicOperatorTypes operation_;
};

//-----------------------------------------------------------------------------------------------//

class SeqStatement : public Statement {
 public:
  SeqStatement(const Statement* left, const Statement* right);
  SeqStatement(std::unique_ptr<const Statement> left,
               std::unique_ptr<const Statement> right);
  ~SeqStatement();

  const Statement* LeftStatement() const { return leftStatement_.get(); }
  const Statement* RightStatement() const { return rightStatement_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  std::unique_ptr<const Statement> Clone() const override;

 private:
  std::unique_ptr<const Statement> leftStatement_;
  std::unique_ptr<const Statement> rightStatement_;
};

//-----------------------------------------------------------------------------------------------//

class LabelStatement : public Statement {
 public:
  LabelStatement(Address label);
  ~LabelStatement();

  Address Label() const { return label_; }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  std::unique_ptr<const Statement> Clone() const override;

 private:
  Address label_;
};

//-----------------------------------------------------------------------------------------------//

class StatementList : public Statement {
 public:
  StatementList() = default;

  StatementList(const Statement* statement) { Add(statement); }
  StatementList(std::unique_ptr<const Statement> statement) {
    Add(std::move(statement));
  }

  void Add(const Statement* statement) { statements_.emplace_back(statement); }
  void Add(std::unique_ptr<const Statement> statement) {
    statements_.push_back(std::move(statement));
  }

  const std::vector<std::unique_ptr<const Statement>>& Statements() const {
    return statements_;
  }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  std::unique_ptr<const Statement> Clone() const override;

 private:
  std::vector<std::unique_ptr<const Statement>> statements_;
};

}  // namespace Irt
