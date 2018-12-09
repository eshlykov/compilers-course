#include "address.hpp"
#include <cassert>

namespace Irt {

    Address::Address() :
        id_{counter_} {
        ++counter_;
    }

    Address::Address(const std::string& label) :
        id_{std::stoi(label)} {
        assert(id_ <= counter_);
        counter_ = id_ + 1;
    }

    std::string Address::ToString() const {
        return std::to_string(id_);
    }

    int Address::counter_ = 0;

}
