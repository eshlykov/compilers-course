#pragma once

#include <string>

namespace Irt {

    enum class SystemFunction : int {
        New,
        Print
    };

    class Address {
    public:
        Address();

        explicit Address(SystemFunction name);

        std::string ToString() const;

    private:
        static int counter_;
        int id_;
    };

}
