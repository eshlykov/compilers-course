#pragma once

#include <fstream>
#include <string>
#include <vector>

class SourceCode {
public:
    explicit SourceCode(const std::string& filename);

    std::string GetFilename() const;

    const std::string& operator[](int index) const;

private:
    std::string filename_;
    std::vector<std::string> lines_;
};
