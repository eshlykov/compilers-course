#include <parser.hpp>
#include <utils/bison-parser.hpp>

using namespace Ast;

const Program* BisonParser::BuildAst(const std::string& inputFilePath) {
  Program* root;

  FILE* inputStream = fopen(inputFilePath.c_str(), "r");
  if (inputStream == nullptr) {
    throw std::invalid_argument("Cannot open file: " + inputFilePath);
  }
  yyin = inputStream;
  do {
    yyparse(&root);
  } while (feof(yyin) == 0);
  fclose(inputStream);

  return root;
}
