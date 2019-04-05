#include "frame.hpp"
#include <algorithm>
#include <cassert>

namespace Ct {

    Frame::Frame(const std::string& name, Address returnAddress) :
        returnAddress_{returnAddress},
        name_{name},
        resultStorage_{InFrameAccess{WordSize_}},
        thisPointer_{InFrameAccess{2 * WordSize_}},
        size_{3 * WordSize_} {
    }

    void Frame::AddFormalParameter(const std::string& name) {
        AddInStorage(name, formalParameters_);
    }

    void Frame::AddLocalVariable(const std::string& name) {
        AddInStorage(name, localVariables_);
    }

    std::shared_ptr<Expression> Frame::GetData(const std::string& name) {
        std::shared_ptr<const Access> access = FindFormalParameterOrLocalVariable(name);
        return access != nullptr ? access->GetData() : nullptr;
    }

    std::shared_ptr<Expression> Frame::GetThis() {
        return thisPointer_.GetData();
    }

    std::shared_ptr<Expression> Frame::GetResultStorage() {
        return resultStorage_.GetData();
    }

    std::shared_ptr<const Access> Frame::FindFormalParameterOrLocalVariable(const std::string& name) const {
        auto access = FindInStorage(name, formalParameters_);
        access = access != nullptr ? access : FindInStorage(name, localVariables_);
        return access;
    }

    void Frame::AddInStorage(const std::string& name, std::vector<KeyType>& storage) {
        auto iter = std::find_if(storage.begin(), storage.end(), [&name] (KeyType key) {
            return key.first == name;
        });
        assert(iter == storage.end());
        storage.emplace_back(name, std::make_shared<const InFrameAccess>(size_));
        size_ += WordSize_;
    }

    std::shared_ptr<const Access> Frame::FindInStorage(const std::string& name, const std::vector<KeyType>& storage) const {
        auto iter = std::find_if(storage.begin(), storage.end(), [&name] (KeyType key) {
            return key.first == name;
        });
        return iter != storage.end() ? iter->second : nullptr;
    }

    const Storage Frame::FramePointer_;

}
