#include "arguments-count-mismatch.hpp"

ArgumentsCountMismatch::ArgumentsCountMismatch(const std::string& message, const Location& location) :
    CompileError(message, location) {
}
