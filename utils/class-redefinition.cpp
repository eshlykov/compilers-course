#include "class-redefenition.hpp"

ClassRedefinition::ClassRedefinition(const std::string& message, const Location& location) :
    CompileError(message, location) {
}
