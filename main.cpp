#include "visitor/printer.hpp"

extern int yyparse(Program*&);

int main() {
    Program* program = nullptr;
    yyparse(program);

    Printer printer{"ast.dot"};
    printer.Visit(program);
}
