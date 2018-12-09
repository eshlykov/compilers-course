#pragma once

#include <string>

namespace Irt {

    class Address {
    public:
        Address();

        explicit Address(const std::string& label);

        std::string ToString() const;

    private:
        static int counter_;
        int id_;
    };
}
