#include <cassert>
#include <irt/frame/frame.hpp>

using namespace Irt;

std::unique_ptr<const Expression> AddressInFrame::ToExpression() const {
  std::unique_ptr<const Expression> offsetExpression;
  if (offset_ != 0) {
    offsetExpression =
        std::move(std::unique_ptr<const Expression>(new BinaryExpression(
            OperatorTypes::Plus, std::move(frameAddress_->ToExpression()),
            std::move(std::unique_ptr<const Expression>(
                new ConstExpression(offset_))))));
  } else {
    offsetExpression = std::move(frameAddress_->ToExpression());
  }
  return std::move(std::unique_ptr<const Expression>(
      new MemExpression(std::move(offsetExpression))));
}

std::unique_ptr<const Expression> AddressOfField::ToExpression() const {
  std::unique_ptr<const Expression> offsetExpression;
  if (offset_ != 0) {
    offsetExpression =
        std::move(std::unique_ptr<const Expression>(new BinaryExpression(
            OperatorTypes::Plus, std::move(thisAddress_->ToExpression()),
            std::move(std::unique_ptr<const Expression>(
                new ConstExpression(offset_))))));
  } else {
    offsetExpression = std::move(thisAddress_->ToExpression());
  }
  return std::move(std::unique_ptr<const Expression>(
      new MemExpression(std::move(offsetExpression))));
}

std::unique_ptr<const Expression> AddressInRegister::ToExpression() const {
  return std::move(
      std::unique_ptr<const Expression>(new TempExpression(storage_)));
}

const int Frame::wordSize_ = 4;
const std::string Frame::thisAddressName_ = "$this";
const std::string Frame::returnAddressName_ = "$return";
const std::string Frame::returnValueAddressName_ = "$rv";
const std::string Frame::framePointerAddressName_ = "$fp";

Frame::Frame(const std::string& className, const std::string& methodName)
    : className_(className),
      methodName_(methodName),
      name_(className + "$" + methodName),
      maxOffsetFramePointer_(0),
      maxOffsetThis_(0) {
  AddAddress(framePointerAddressName_,
             new AddressInRegister(Storage(framePointerAddressName_)));
  AddAddress(returnValueAddressName_,
             new AddressInRegister(Storage(returnValueAddressName_)));
}

int Frame::GetWordSize() const { return wordSize_; }

Address Frame::GetName() const { return name_; }

const std::string& Frame::GetClassName() const { return className_; }

const std::string& Frame::GetMethodName() const { return methodName_; }

void Frame::AddThisAddress() { AddArgumentAddress(thisAddressName_); }

void Frame::AddReturnAddress() { AddArgumentAddress(returnAddressName_); }

void Frame::AddArgumentAddress(const std::string& name) {
  AddLocalAddress(name);
}

void Frame::AddLocalAddress(const std::string& name) {
  const AddressInFrame* address = new AddressInFrame(
      GetFramePointerAddress(), NextOffsetFromFramePointer());
  AddAddress(name, address);
}

void Frame::AddFieldAddress(const std::string& name) {
  const AddressOfField* address =
      new AddressOfField(GetThisAddress(), NextOffsetFromThis());
  AddAddress(name, address);
}

const IAddress* Frame::GetAddress(const std::string& varName) const {
  auto addressIt = addresses_.find(varName);
  const IAddress* res = nullptr;
  if (addressIt != addresses_.end()) {
    res = addressIt->second.get();
  }
  return res;
}

const IAddress* Frame::GetThisAddress() const {
  return GetAddress(thisAddressName_);
}

const IAddress* Frame::GetReturnAddress() const {
  return GetAddress(returnAddressName_);
}

const IAddress* Frame::GetFramePointerAddress() const {
  return GetAddress(framePointerAddressName_);
}

const IAddress* Frame::GetReturnValueAddress() const {
  return GetAddress(returnValueAddressName_);
}

std::unique_ptr<const Expression> Frame::ExternalCall(
    const std::string& functionName,
    std::unique_ptr<const ExpressionList> args) const {
  return std::move(std::unique_ptr<const Expression>(
      new Irt::CallExpression(std::move(std::unique_ptr<const Expression>(
                                  new NameExpression(Address(functionName)))),
                              std::move(args))));
}

int Frame::NextOffsetFromFramePointer() {
  int prevMaxOffsetFramePointer = maxOffsetFramePointer_;
  maxOffsetFramePointer_ += wordSize_;
  return prevMaxOffsetFramePointer;
}

int Frame::NextOffsetFromThis() {
  int prevMaxOffsetThis = maxOffsetThis_;
  maxOffsetThis_ += wordSize_;
  return prevMaxOffsetThis;
}

void Frame::AddAddress(const std::string& name, const IAddress* address) {
  auto result =
      addresses_.emplace(name, std::unique_ptr<const IAddress>(address));
  // overwriting may happen in case there is a field and a local/argument with
  // the same name assert( result.second );
}
