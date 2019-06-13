#include <ast/node/program.hpp>
#include <memory>
#include <string>

extern "C" FILE* yyin;
extern "C" FILE* yyout;

class BisonParser {
 public:
  explicit BisonParser(std::string inputFilePath)
      : inputFilePath_(std::move(inputFilePath)) {}
  const Ast::Program* BuildAst(const std::string& inputFilePath);

 private:
  std::string inputFilePath_;
};
