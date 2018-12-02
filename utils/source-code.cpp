#include "source-code.hpp"
#include <algorithm>
#include <cctype>

SourceCode::SourceCode(const std::string& filename) :
    filename_{filename} {
    std::ifstream stream{filename_};

    std::string line;
    while (std::getline(stream, line)) {
        std::replace_if(line.begin(), line.end(), [] (char symbol) {
            return std::isspace(static_cast<int>(symbol)) != 0;
        }, ' ');
        lines_.push_back(line);
    }
    lines_.push_back(" ");

    stream.close();
}

std::string SourceCode::GetFilename() const {
    return filename_;
}

const std::string& SourceCode::operator[](int index) const {
    return lines_[index - 1];
}
