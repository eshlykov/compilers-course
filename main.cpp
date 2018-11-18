#include "ast/program.hpp"
#include "compile-error.hpp"
#include "visitor/printer/printer.hpp"
#include "visitor/symbol-table/symbol-table.hpp"
#include <iostream>
#include <memory>

extern int yyparse(std::unique_ptr<Program>&);

std::string ParseDrawingFilenameFromArguments(int argc, char *argv[]) {
    if (argc == 2) {
        return argv[1];
    }

    return "ast.dot";
}

/*
 * To use our compiler now you should provide name of .dot file as first argument
 */
int main(int argc, char *argv[]) {
    std::unique_ptr<Program> program = nullptr;
    if (yyparse(program) != 0) {
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
            std::cout << error.GetMessage() << std::endl;
        }
        return 1;
    }
}
