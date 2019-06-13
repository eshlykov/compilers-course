#pragma once

#include <unordered_map>
#include <vector>

#include <irt/node/expression.hpp>
#include <utils/address.hpp>
#include <utils/storage.hpp>

namespace Irt {

class IAddress {
 public:
  virtual ~IAddress() {}
  virtual std::unique_ptr<const Expression> ToExpression() const = 0;
};

/**
Indicates a memory location at offset X from the frame pointer.
*/
class AddressInFrame : public IAddress {
 public:
  AddressInFrame(const IAddress* frameAddress, int offset)
      : frameAddress_(frameAddress), offset_(offset) {}

  virtual ~AddressInFrame() {}
  virtual std::unique_ptr<const Expression> ToExpression() const override;

 private:
  const IAddress* frameAddress_;
  int offset_;
};

class AddressOfField : public IAddress {
 public:
  AddressOfField(const IAddress* thisAddress, int offset)
      : thisAddress_(std::move(thisAddress)), offset_(offset) {}
  std::unique_ptr<const Expression> ToExpression() const override;

 private:
  const IAddress* thisAddress_;
  int offset_;
};

/**
CAddressInRegister (T84) indicates that it will be held in "register" T84
*/
class AddressInRegister : public IAddress {
 public:
  AddressInRegister(const Storage& storage) : storage_(storage) {}
  std::unique_ptr<const Expression> ToExpression() const override;

 private:
  Storage storage_;
};

class Frame {
 public:
  // CFrame( CLabel _name ) : name( _name ), maxOffsetFramePointer( 0 ) {}
  Frame(const std::string& className, const std::string& methodName);

  int GetWordSize() const;

  Address GetName() const;
  const std::string& GetClassName() const;
  const std::string& GetMethodName() const;

  // reserves place on stack for method arguments and locals (determines offsets
  // for them)
  void AddThisAddress();
  void AddReturnAddress();
  void AddArgumentAddress(const std::string& name);
  void AddLocalAddress(const std::string& name);
  void AddFieldAddress(const std::string& name);

  const IAddress* GetFramePointerAddress() const;
  const IAddress* GetReturnValueAddress() const;
  const IAddress* GetThisAddress() const;
  const IAddress* GetReturnAddress() const;
  const IAddress* GetAddress(const std::string& varName) const;

  std::unique_ptr<const Expression> ExternalCall(
      const std::string& functionName,
      std::unique_ptr<const ExpressionList> args) const;

 private:
  int NextOffsetFromFramePointer();
  int NextOffsetFromThis();
  void AddAddress(const std::string& name, const IAddress* address);

  std::string className_;
  std::string methodName_;
  Address name_;
  std::unordered_map<std::string, std::unique_ptr<const IAddress>> addresses_;

  static const int wordSize_;
  static const std::string thisAddressName_;
  static const std::string returnAddressName_;
  static const std::string returnValueAddressName_;
  static const std::string framePointerAddressName_;

  int maxOffsetFramePointer_;
  int maxOffsetThis_;
};

}  // namespace Irt
