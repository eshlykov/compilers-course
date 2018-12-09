#pragma once

#include "access.hpp"

class InFrameAccess : public Access {
public:
    InFrameAccess(int offset);

private:
    int offset_;
};
