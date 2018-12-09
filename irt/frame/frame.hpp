#pragma once

#include "access.hpp"
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace Irt {

    class Frame {
    public:
        explicit Frame(const std::string& name);

        void AddFormalParameter(const std::string& name);

        void AddLocalVariable(const std::string& name);

        std::shared_ptr<const Access> FindFormalParameterOrLocalVariable(const std::string& name) const;

    private:
        using KeyType = std::pair<std::string, std::shared_ptr<const Access>>;

        void AddInStorage(const std::string& name, std::vector<KeyType>& storage);

        std::shared_ptr<const Access> FindInStorage(const std::string& name, const std::vector<KeyType>& storage) const;

    private:
        const std::string name_;
        int size_;
        std::vector<KeyType> formalParameters_;
        std::vector<KeyType> localVariables_;

        static constexpr int variableSize_ = sizeof(nullptr);
    };

}
