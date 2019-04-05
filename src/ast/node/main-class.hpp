#pragma once

#include <memory>
#include <string>
#include "node.hpp"
#include "statement.hpp"

namespace Ast {

class MainClass : public Node {
 public:
  MainClass(Location location, std::string className, std::string argv,
            std::unique_ptr<Statement> mainBody);

  void Accept(Visitor* visitor) final;

 public:
  const std::string className_;
  const std::string argv_;
  const std::unique_ptr<Statement> mainBody_;
};

inline MainClass::MainClass(Location location, std::string className,
                            std::string argv,
                            std::unique_ptr<Statement> mainBody)
    : className_{std::move(className)},
      argv_{std::move(argv)},
      mainBody_{std::move(mainBody)} {
  SetLocation(location);
  assert(mainBody_ != nullptr);
}

inline void MainClass::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Ast
