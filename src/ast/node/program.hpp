#pragma once

#include <memory>

#include <ast/node/visitor-target.hpp>
#include <ast/visitor/visitor.hpp>

#include <ast/node/class-declaration-list.hpp>
#include <ast/node/main-class.hpp>

namespace Ast {

class Program : public VisitorTarget {
 public:
  Program(const MainClass* mainClass,
          const ClassDeclarationList* classDeclarations,
          const Location& location)
      : VisitorTarget(location),
        mainClass_(mainClass),
        classDeclarations_(classDeclarations) {}

  const MainClass* GetMainClass() const { return mainClass_.get(); }
  const ClassDeclarationList* ClassDeclarations() const {
    return classDeclarations_.get();
  }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::unique_ptr<const MainClass> mainClass_;
  std::unique_ptr<const ClassDeclarationList> classDeclarations_;
};

}  // namespace Ast
