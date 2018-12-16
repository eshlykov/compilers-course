#include "address.hpp"
#include <cassert>

namespace Irt {

    Address::Address() :
        id_{counter_} {
        ++counter_;
    }

    Address::Address(SystemFunction name) :
        id_{static_cast<std::underlying_type_t<SystemFunction>>(name)} {
        counter_ = id_ + 1;
    }

    std::string Address::ToString() const {
        return std::to_string(id_);
    }

    int Address::counter_ = 1024; // More than quantity of system function

}
