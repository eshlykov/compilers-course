#include "ast/program.hpp"
#include "compile-error.hpp"
#include "source-code.hpp"
#include "visitor/printer/printer.hpp"
#include "visitor/symbol-table/symbol-table.hpp"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <memory>

extern FILE* yyin;
extern int yyparse(std::unique_ptr<Program>&, const SourceCode&);

std::string ParseDrawingFilenameFromArguments(int argc, char *argv[]) {
    if (argc == 3) {
        return argv[2];
    }
    return "ast.dot";
}

/*
 * To use our compiler now you should provide name of .dot file as first argument
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "no source filename is given" << std::endl;
        return 1;
    }

    std::unique_ptr<Program> program = nullptr;

    std::string filename = argv[1];
    SourceCode sourceCode{filename};

    yyin = std::fopen(filename.c_str(), "r");
    if (yyparse(program, sourceCode) != 0) {
        std::cout << "yyparse failed" << std::endl;
        return 1;
    }

    if (program == nullptr) {
        std::cout << "program is nullptr" << std::endl;
        return 1;
    }

    if (program->isErroneous_) {
        std::cout << "program is erroneous" << std::endl;
        return 1;
    }

    Printer{"ast.dot"};

    Printer printer{ParseDrawingFilenameFromArguments(argc, argv)};
    printer.Visit(program.get());

    SymbolTable symbolTable{};
    try {
        symbolTable.Visit(program.get());
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
