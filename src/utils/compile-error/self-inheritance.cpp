#include "self-inheritance.hpp"

SelfInheritance::SelfInheritance(const std::string& message,
                                 const Location& location)
    : CompileError(message, location) {}
