#pragma once

#include <fstream>
#include <string>
#include <vector>

class SourceCode {
 public:
  explicit SourceCode(std::string filename);

  std::string GetFilename() const;

  const std::string& operator[](int index) const;

 private:
  std::string filename_;
  std::vector<std::string> lines_;
};

inline SourceCode::SourceCode(std::string filename)
    : filename_{std::move(filename)} {
  std::ifstream stream{filename_};

  std::string line;
  while (std::getline(stream, line)) {
    std::replace_if(
        line.begin(), line.end(),
        [](char symbol) { return std::isspace(static_cast<int>(symbol)) != 0; },
        ' ');
    lines_.push_back(line);
  }
  lines_.emplace_back(" ");

  stream.close();
}

inline std::string SourceCode::GetFilename() const { return filename_; }

inline const std::string& SourceCode::operator[](int index) const {
  return lines_[index - 1];
}
