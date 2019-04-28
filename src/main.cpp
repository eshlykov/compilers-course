#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include "ast/node/program.hpp"
#include "ast/visitor/printer/printer.hpp"
#include "ast/visitor/symbol-table/symbol-table.hpp"
#include "ast/visitor/translator/translator.hpp"
#include "ct/visitor/printer/code-fragment-printer.hpp"
#include "irt/visitor/printer/code-fragment-printer.hpp"
#include "irt/visitor/translator/code-fragment-translator.hpp"
#include "utils/compile-error/compile-error.hpp"
#include "utils/parser-args.hpp"
#include "utils/source-code.hpp"

extern FILE* yyin;
extern int yyparse(ParserArgs&);

std::string ParseDrawingFilenameFromArguments(int argc, char* argv[]) {
  if (argc == 3) {
    return argv[2];
  }
  return "ast.dot";
}

/*
 * To use our compiler now you should provide name of .dot file as first
 * argument
 */
int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "no source filename is given" << std::endl;
    return 1;
  }

  std::string filename = argv[1];
  SourceCode sourceCode{filename};

  yyin = std::fopen(filename.c_str(), "r");
  if (yyin == nullptr) {
    std::cout << "cannot open file " << filename << std::endl;
  }

  ParserArgs parserArgs;
  bool isParsed = yyparse(parserArgs) == 0;

  std::fclose(yyin);

  std::vector<CompileError> errors = parserArgs.errors_;
  if (!errors.empty()) {
    for (auto& error : errors) {
      std::cout << error.GetMessage(sourceCode) << std::endl;
    }
    return 1;
  }

  if (!isParsed) {
    std::cout << CompileError{"unexpected parser error", {}}.GetMessage(
                     sourceCode)
              << std::endl;
    return 1;
  }

  std::unique_ptr<Ast::Program> program = std::move(parserArgs.program_);

  if (program == nullptr) {
    std::cout << CompileError{"program is null pointer", {}}.GetMessage(
                     sourceCode)
              << std::endl;
    return 1;
  }

  // Ast::Printer astPrinter{ParseDrawingFilenameFromArguments(argc, argv)};
  // astPrinter.Visit(program.get());

  Ast::SymbolTable symbolTable{};
  try {
    symbolTable.Visit(program.get());
  } catch (const std::exception& exception) {
    std::cout << exception.what() << std::endl;
    return 1;
  } catch (...) {
    std::cout << "unexpected error" << std::endl;
    return 1;
  }

  if (auto redefinitions = symbolTable.GetErrorList(); !redefinitions.empty()) {
    for (auto& error : redefinitions) {
      std::cout << error.GetMessage(sourceCode) << std::endl;
    }
    return 1;
  }

  Ast::Translator translator;
  translator.Visit(program.get());

//    Irt::Print(ParseDrawingFilenameFromArguments(argc, argv),
//               translator.GetCodeFragment());

  std::shared_ptr<Ct::CodeFragment> codeFragment =
      Irt::Translate(translator.GetCodeFragment());

  Ct::Print(ParseDrawingFilenameFromArguments(argc, argv), codeFragment);
}
