#pragma once

#include <string>

namespace Ct {

    class Storage {
    public:
        Storage();

        std::string ToString() const;

        bool operator==(const Storage& other) const;

    private:
        static int counter_;
        int id_;
    };

}
