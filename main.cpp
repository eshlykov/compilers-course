#include "ast/program.hpp"
#include "compile-error.hpp"
#include "parser-args.hpp"
#include "source-code.hpp"
#include "visitor/printer/printer.hpp"
#include "visitor/symbol-table/symbol-table.hpp"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <memory>

extern FILE* yyin;
extern int yyparse(ParserArgs&);

std::string ParseDrawingFilenameFromArguments(int argc, char* argv[]) {
    if (argc == 3) {
        return argv[2];
    }
    return "ast.dot";
}

/*
 * To use our compiler now you should provide name of .dot file as first argument
 */
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "no source filename is given" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    SourceCode sourceCode{filename};

    yyin = std::fopen(filename.c_str(), "r");
    ParserArgs parserArgs;
    bool isParsed = yyparse(parserArgs) == 0;

    std::vector<CompileError> errors = parserArgs.errors_;
    if (!errors.empty()) {
        for (auto& error : errors) {
            std::cout << error.GetMessage(sourceCode) << std::endl;
        }
        return 1;
    }

    if (!isParsed) {
        std::cout << CompileError{"unxpected parser error", {1, 1, 1}}.GetMessage(sourceCode) << std::endl;
        return 1;
    }

    std::unique_ptr<Program> program = std::move(parserArgs.program_);

    if (program == nullptr) {
        std::cout << CompileError{"program is null pointer", {1, 1, 1}}.GetMessage(sourceCode) << std::endl;
        return 1;
    }


    Printer{"ast.dot"};

    Printer printer{ParseDrawingFilenameFromArguments(argc, argv)};
    printer.Visit(program.get());

    SymbolTable symbolTable{};
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
}
