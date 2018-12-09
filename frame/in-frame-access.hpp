#pragma once

#include "access.hpp"

class InFrameAccess : public Access {
public:
    explicit InFrameAccess(int offset);

private:
    int offset_;
};
