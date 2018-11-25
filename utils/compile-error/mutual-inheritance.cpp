#include "mutual-inheritance.hpp"
#include "compile-error.hpp"
#include "../location.hpp"
#include <string>

MutualInheritance::MutualInheritance(const std::string& message, const Location& location) :
    CompileError(message, location) {
}
