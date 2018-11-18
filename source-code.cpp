#include "source-code.hpp"
#include <algorithm>

SourceCode::SourceCode(const std::string& filename) :
    filename_{filename} {
    std::ifstream stream{filename_};

    std::string line;
    while (std::getline(stream, line)) {
        std::replace(line.begin(), line.end(), '\t', ' ');
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        lines_.push_back(line);
    }

    stream.close();
}

std::string SourceCode::GetFilename() const {
    return filename_;
}

const std::string& SourceCode::operator[](int index) const {
    return lines_[index - 1];
}
