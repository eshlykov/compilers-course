#pragma once

#include <string>

#include <utils/compilation-phase.hpp>

class Compiler {
 public:
  Compiler(std::string pathInputFile, std::string pathOutputDir)
      : pathInputFile_(std::move(pathInputFile)),
        pathOutputDir_(std::move(pathOutputDir)) {}

  void Run();

 private:
  std::string pathInputFile_;
  std::string pathOutputDir_;
};
