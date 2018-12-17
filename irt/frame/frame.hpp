#pragma once

#include "../utils/storage.hpp"
#include "../node/expression.hpp"
#include "in-frame-access.hpp"
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

        std::shared_ptr<Expression> GetData(const std::string& name);

        std::shared_ptr<Expression> GetThis();

    private:
        using KeyType = std::pair<std::string, std::shared_ptr<const Access>>;

        std::shared_ptr<const Access> FindFormalParameterOrLocalVariable(const std::string& name) const;

        void AddInStorage(const std::string& name, std::vector<KeyType>& storage);

        std::shared_ptr<const Access> FindInStorage(const std::string& name, const std::vector<KeyType>& storage) const;

    public:
        static constexpr int WordSize_ = sizeof(nullptr);
        static const Storage FramePointer_;

    private:
        const std::string name_;
        const InFrameAccess thisPointer_;
        int size_;
        std::vector<KeyType> formalParameters_;
        std::vector<KeyType> localVariables_;
    };

}
