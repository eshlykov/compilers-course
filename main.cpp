#include "ast/program.hpp"
#include "compile-error.hpp"
#include "visitor/printer.hpp"
#include "visitor/symbol-table.hpp"
#include <iostream>

extern int yyparse(Program*&);

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


    Program* program = nullptr;
    yyparse(program);

    if (program && program->isErroneous_) {
        delete program;
        return 1;
    } else if (!program) {
        return 1;
    }

    Printer printer{ParseDrawingFilenameFromArguments(argc, argv)};
    printer.Visit(program);

    SymbolTable symbolTable{};
    try {
        symbolTable.Visit(program);
    } catch (const CompileError& error) {
        std::cout << error.GetMessage() << std::endl;
        delete program;
        return 1;
    }

    delete program;
    return 0;
}
