#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "../../utils/address.hpp"
#include "../../utils/storage.hpp"
#include "../node/expression.hpp"
#include "in-frame-access.hpp"

namespace Ct {

class Frame {
 public:
  explicit Frame(std::string name, Address returnAddress = {});

  void AddFormalParameter(const std::string& name);

  void AddLocalVariable(const std::string& name);

  ExpressionPtr GetData(const std::string& name);

  ExpressionPtr GetThis();

  ExpressionPtr GetResultStorage();

 private:
  using KeyType = std::pair<std::string, std::shared_ptr<const Access>>;

  std::shared_ptr<const Access> FindFormalParameterOrLocalVariable(
      const std::string& name) const;

  void AddInStorage(const std::string& name, std::vector<KeyType>& storage);

  std::shared_ptr<const Access> FindInStorage(
      const std::string& name, const std::vector<KeyType>& storage) const;

 public:
  static constexpr int WordSize_ = sizeof(nullptr);
  static const Storage FramePointer_;

 public:
  const Address returnAddress_;

 private:
  const std::string name_;
  const InFrameAccess resultStorage_;
  const InFrameAccess thisPointer_;
  int size_;
  std::vector<KeyType> formalParameters_;
  std::vector<KeyType> localVariables_;
};

}  // namespace Ct
