#pragma once

class ClassRedefinition : public CompileError {
public:
    ClassRedefinition(const std::string& message, const Location& location);
};
