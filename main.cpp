#include "ast/program.hpp"
#include "compile-error.hpp"
#include "visitor/printer.hpp"
#include "visitor/symbol-table.hpp"
#include <iostream>

extern int yyparse(Program*&);

int main() {
    Program* program = nullptr;
    yyparse(program);

    Printer printer{"ast.dot"};
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
