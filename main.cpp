#include "ast/class-declaration.hpp"
#include "ast/class-declaration-repeated.hpp"
#include "ast/comma-type-identifier.hpp"
#include "ast/comma-type-identifier-repeated.hpp"
#include "ast/extends-identifier-optional.hpp"
#include "ast/goal.hpp"
#include "ast/main-class.hpp"
#include "ast/method-declaration.hpp"
#include "ast/type-identifier-comma-type-identifier-repeated.hpp"
#include "ast/type-identifier-comma-type-identifier-repeated-optional.hpp"
#include "ast/var-declaration.hpp"
#include "ast/var-declaration-repeated.hpp"

extern int yyparse();

int main() {
    yyparse();
}
