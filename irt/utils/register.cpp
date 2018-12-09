#include "register.hpp"

namespace Irt {

    Register::Register() :
        id_{counter_} {
        ++counter_;
    }

    std::string Register::ToString() const {
        return std::to_string(id_);
    }

    int Register::counter_ = 0;

}
