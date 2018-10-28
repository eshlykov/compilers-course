#include "visitor/printer.hpp"

extern int yyparse(Goal*&);

int main() {
    Goal* goal = nullptr;
    yyparse(goal);

    Printer printer{"ast.dot"};
    printer.Visit(goal);
}
