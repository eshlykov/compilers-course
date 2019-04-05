#include "mutual-inheritance.hpp"
#include <string>
#include "../location.hpp"
#include "compile-error.hpp"

MutualInheritance::MutualInheritance(const std::string& message,
                                     const Location& location)
    : CompileError(message, location) {}
