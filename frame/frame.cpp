#include "in-frame-access.hpp"
#include "frame.hpp"
#include <algorithm>
#include <cassert>

Frame::Frame(const std::string& name) :
    name_{name},
    size_{0} {
}

void Frame::AddFormalParameter(const std::string& name) {
    AddInStorage(name, formalParameters_);
}

void Frame::AddLocalVariable(const std::string& name) {
    AddInStorage(name, localVariables_);
}

std::shared_ptr<const Access> Frame::FindFormalParameterOrLocalVariable(const std::string& name) const {
    auto access = FindInStorage(name, formalParameters_);
    access = access != nullptr ? access : FindInStorage(name, localVariables_);
    assert(access != nullptr);
    return access;
}

void Frame::AddInStorage(const std::string& name, std::vector<KeyType>& storage) {
    auto iter = std::find_if(storage.begin(), storage.end(), [&name] (KeyType key) {
        return key.first == name;
    });
    assert(iter != storage.end());
    storage.emplace_back(name, std::make_shared<const InFrameAccess>(size_));
    size_ += ptrSize_;
}

std::shared_ptr<const Access> Frame::FindInStorage(const std::string& name, const std::vector<KeyType>& storage) const {
    auto iter = std::find_if(storage.begin(), storage.end(), [&name] (KeyType key) {
        return key.first == name;
    });
    return iter != storage.end() ? iter->second : nullptr;
}
