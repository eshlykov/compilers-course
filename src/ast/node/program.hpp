#pragma once

#include <memory>
#include <vector>
#include "class-declaration.hpp"
#include "main-class.hpp"
#include "node.hpp"

namespace Ast {

class Program : public Node {
 public:
  Program(Location location, std::unique_ptr<MainClass> mainClass,
          std::vector<std::unique_ptr<ClassDeclaration>>& classDeclarations);

  void Accept(Visitor* visitor) final;

 public:
  const std::unique_ptr<MainClass> mainClass_;
  const std::vector<std::unique_ptr<ClassDeclaration>> classDeclarations_;
};

inline Program::Program(
    Location location, std::unique_ptr<MainClass> mainClass,
    std::vector<std::unique_ptr<ClassDeclaration>>& classDeclarations)
    : mainClass_{std::move(mainClass)},
      classDeclarations_{std::move(classDeclarations)} {
  SetLocation(location);
  assert(mainClass_ != nullptr);
}

inline void Program::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Ast
