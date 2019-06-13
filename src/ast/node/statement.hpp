#pragma once

#include <memory>
#include <vector>

#include <ast/node/visitor-target.hpp>
#include <ast/visitor/visitor.hpp>

#include <ast/node/expression.hpp>

namespace Ast {

class Statement : public VisitorTarget {
 public:
  Statement(const Location& location) : VisitorTarget(location) {}
  virtual ~Statement() {}
};

class StatementList;
//-----------------------------------------------------------------------------------------------//

class AssignIdStatement : public Statement {
 public:
  AssignIdStatement(const IdExpression* leftPart, const Expression* rightPart,
                    const Location& location)
      : Statement(location), leftPart_(leftPart), rightPart_(rightPart) {}

  const IdExpression* LeftPart() const { return leftPart_.get(); }
  const Expression* RightPart() const { return rightPart_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::unique_ptr<const IdExpression> leftPart_;
  std::unique_ptr<const Expression> rightPart_;
};

//-----------------------------------------------------------------------------------------------//

class AssignIdWithIndexStatement : public Statement {
 public:
  AssignIdWithIndexStatement(const IdExpression* leftPartId,
                             const Expression* leftPartIndex,
                             const Expression* rightPart,
                             const Location& location)
      : Statement(location),
        leftPartId_(leftPartId),
        leftPartIndex_(leftPartIndex),
        rightPart_(rightPart) {}

  const IdExpression* LeftPartId() const { return leftPartId_.get(); }
  const Expression* LeftPartIndex() const { return leftPartIndex_.get(); }
  const Expression* RightPart() const { return rightPart_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::unique_ptr<const IdExpression> leftPartId_;
  std::unique_ptr<const Expression> leftPartIndex_;
  std::unique_ptr<const Expression> rightPart_;
};

//-----------------------------------------------------------------------------------------------//

class PrintStatement : public Statement {
 public:
  PrintStatement(const Expression* printTarget, const Location& location)
      : Statement(location), printTarget_(printTarget) {}

  const Expression* PrintTarget() const { return printTarget_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::unique_ptr<const Expression> printTarget_;
};

//-----------------------------------------------------------------------------------------------//

class ConditionalStatement : public Statement {
 public:
  ConditionalStatement(const Expression* condition,
                       const Statement* positiveTarget,
                       const Statement* negativeTarget,
                       const Location& location)
      : Statement(location),
        condition_(condition),
        positiveTarget_(positiveTarget),
        negativeTarget_(negativeTarget) {}

  const Expression* Condition() const { return condition_.get(); }
  const Statement* PositiveTarget() const { return positiveTarget_.get(); }
  const Statement* NegativeTarget() const { return negativeTarget_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::unique_ptr<const Expression> condition_;
  std::unique_ptr<const Statement> positiveTarget_;
  std::unique_ptr<const Statement> negativeTarget_;
};

//-----------------------------------------------------------------------------------------------//

class WhileLoopStatement : public Statement {
 public:
  WhileLoopStatement(const Expression* condition, const Statement* body,
                     const Location& location)
      : Statement(location), condition_(condition), body_(body) {}

  const Expression* Condition() const { return condition_.get(); }
  const Statement* Body() const { return body_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::unique_ptr<const Expression> condition_;
  std::unique_ptr<const Statement> body_;
};

//-----------------------------------------------------------------------------------------------//

class BracesStatement : public Statement {
 public:
  BracesStatement(const StatementList* list, const Location& location)
      : Statement(location), list_(list) {}

  const StatementList* List() const { return list_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::unique_ptr<const StatementList> list_;
};

}  // namespace Ast
