#pragma once

#include "compile-error/compile-error.hpp"

namespace Ast {

class Program;

}

struct ParserArgs {
  std::unique_ptr<Ast::Program> program_;
  std::vector<CompileError> errors_;
};
