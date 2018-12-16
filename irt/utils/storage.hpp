#pragma once

#include <string>

namespace Irt {

    class Storage {
    public:
        Storage();

        std::string ToString() const;

    private:
        static int counter_;
        int id_;
    };

}
