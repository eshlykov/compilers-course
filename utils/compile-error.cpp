#include "compile-error.hpp"

CompileError::CompileError(const std::string& message, const Location& location) :
    message_{message}, location_{location} {
}

std::string CompileError::GetMessage(const SourceCode& sourceCode) const {

    std::string message = "\033[1;37m";
    message += sourceCode.GetFilename();
    message += ":" + std::to_string(location_.lineNumber_) + ":" + std::to_string(location_.firstColumn_ + 1);

    if (location_.lastColumn_ != location_.firstColumn_) {
        message += "-" + std::to_string(location_.lastColumn_ + 1);

    }

    message += ":";
    message += "\033[0m";
    message += "\033[1;31m error: \033[0m";
    message += "\033[1;37m" + message_ + "\033[0m";
    message += "\n" + sourceCode[location_.lineNumber_] + "\n";

    if (location_.firstColumn_ > 0) {
        message += std::string(location_.firstColumn_ - 1, ' ');
    }

    message += "\033[1;32m";
    message += "^";
    message += std::string(location_.lastColumn_ - location_.firstColumn_, '~');
    message += "\033[0m";

    return message;
}
