extern int yyparse();

int main() {
    while (yyparse() == 0) {
    }
}
