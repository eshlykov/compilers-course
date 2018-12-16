#pragma once

#include <string>

namespace Irt {

    class Address {
    public:
        Address();

        explicit Address(const std::string& address);

        std::string ToString() const;

    private:
        static int counter_;
        int id_;
    };

}
