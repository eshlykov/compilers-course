#pragma once

#include <vector>

template <typename T>
void FreeVector(std::vector<T*>& objects) {
    for (auto* object : objects) {
        delete object;
    }
}
