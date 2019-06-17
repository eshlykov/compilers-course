#pragma once

#include <string>
#include <vector>

class AssemblyCommand {
 public:
  AssemblyCommand(std::string text, std::vector<std::string> registers)
      : text_(std::move(text)), registers_(std::move(registers)) {}

  static std::string NewRegister(std::vector<AssemblyCommand>& code) {
    std::string newRegister = "r" + std::to_string(registerCounter_++);
    code.push_back(AssemblyCommand("mov " + newRegister + ", $0", {newRegister}));
    return newRegister;
  }

  const std::string& Text() const { return text_; }

  const std::vector<std::string>& Registers() const { return registers_; }

 private:
  const std::string text_;
  const std::vector<std::string> registers_;

  static int registerCounter_;
};
