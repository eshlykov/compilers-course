#pragma once

#include <string>

namespace Irt {

    class Register {
    public:
        Register();

        std::string ToString() const;

    private:
        static int counter_;
        int id_;
    };
}
