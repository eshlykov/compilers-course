#pragma once

#include <ast/visitor/visitor.hpp>

namespace Ast {

class IVisitorTarget {
 public:
  virtual ~IVisitorTarget() = default;
  virtual void Accept(IVisitor* visitor) const = 0;
};

struct Location {
  Location(int firstLine, int lastLine, int firstColumn, int lastColumn)
      : firstLine_(firstLine),
        lastLine_(lastLine),
        firstColumn_(firstColumn),
        lastColumn_(lastColumn) {}

  int firstLine_;
  int lastLine_;
  int firstColumn_;
  int lastColumn_;
};

class VisitorTarget : public IVisitorTarget {
 public:
  explicit VisitorTarget(const Location& location) : location_(location) {}
  virtual const Location& GetLocation() const { return location_; }

 private:
  Location location_;
};

}  // namespace Ast
