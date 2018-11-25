#include "argument-redefinition.hpp"

ArgumentRedefinition::ArgumentRedefinition(const std::string& message, const Location& location) :
    CompileError(message, location) {
}
