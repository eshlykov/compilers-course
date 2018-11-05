#include "ast/program.hpp"
#include "compile-error.hpp"
#include "visitor/printer.hpp"

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
        std::cout << error.what() << std::endl;
        delete program;
        std::exit(1);
    }

    delete program;
}
