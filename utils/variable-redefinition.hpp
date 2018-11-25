#pragma once

class VariableRedefinition : public CompileError {
public:
    VariableRedefinition(const std::string& message, const Location& location);
};
