#include "storage.hpp"

namespace Irt {

    Storage::Storage() :
        id_{counter_} {
        ++counter_;
    }

    std::string Storage::ToString() const {
        return std::to_string(id_);
    }

    int Storage::counter_ = 0;

}
