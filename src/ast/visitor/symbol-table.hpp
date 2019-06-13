#pragma once

#include <cassert>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

// Predeclarations and general enum and classes declarations

class ClassDefinition;
class MethodDefinition;

enum class AccessModifiers { Public, Private };

enum class TypeIdentifieres {
  Int,
  IntArray,
  Boolean,
  ClassId,

  // Value to return if no valid variable type found
  NotFound
};

void PrintType(TypeIdentifieres type);

// Type identifier class for other methods
class TypeIdentifier {
 public:
  TypeIdentifier() = default;
  explicit TypeIdentifier(TypeIdentifieres type) : type_(type) {
    assert(type != TypeIdentifieres::ClassId);
  }

  explicit TypeIdentifier(std::string className)
      : type_(TypeIdentifieres::ClassId), className_(std::move(className)) {}

  TypeIdentifieres Type() const { return type_; }
  const std::string& ClassName() const { return className_; }

  bool operator==(const TypeIdentifier& other) const {
    if (type_ == other.type_) {
      if (type_ == TypeIdentifieres::ClassId) {
        return className_ == other.className_;
      }
      return true;
    }
    return false;
  }

  bool operator!=(const TypeIdentifier& other) const {
    return !((*this) == other);
  }

 private:
  TypeIdentifieres type_;
  // Valid if Type==TTypeIdentifier::ClassId
  std::string className_;
};

///////////////////////////////////////////////////////////////////////////////////////////////

class SymbolTable {
 public:
  SymbolTable() = default;

  // Add class definition. Return true on success. False if such class already
  // exists
  bool AddClassDefinition(
      const std::string& name,
      std::shared_ptr<const ClassDefinition> classDefinition);
  // Get class definition by name. Returns zero pointer if it doesn't exist
  std::shared_ptr<const ClassDefinition> GetClassDefinition(
      const std::string& name) const;

  std::shared_ptr<const MethodDefinition> SearchClassHierarchyForMethod(
      const std::string& methodName,
      std::shared_ptr<const ClassDefinition> baseClass) const;
  TypeIdentifier SearchClassHierarchyForField(
      const std::string& fieldName,
      std::shared_ptr<const ClassDefinition> baseClass) const;

 private:
  std::unordered_map<std::string, std::shared_ptr<const ClassDefinition>>
      classes_;
};

////////////////////////////////////////////////////////////////////////////////

class ClassDefinition {
 public:
  using NameToMethodDefinitionMap =
      std::unordered_map<std::string, std::shared_ptr<const MethodDefinition>>;
  using NameToFieldTypeMap = std::unordered_map<std::string, TypeIdentifier>;

  // Create class defintion without parent
  ClassDefinition(std::string className,
                  std::shared_ptr<NameToMethodDefinitionMap> methods,
                  std::shared_ptr<NameToFieldTypeMap> fields)
      : className_(std::move(className)),
        hasParent_(false),
        methods_(std::move(methods)),
        fields_(std::move(fields)) {}

  ClassDefinition(std::string className, std::string parentName,
                  std::shared_ptr<NameToMethodDefinitionMap> methods,
                  std::shared_ptr<NameToFieldTypeMap> fields)
      : className_(std::move(className)),
        parentName_(std::move(parentName)),
        hasParent_(true),
        methods_(std::move(methods)),
        fields_(std::move(fields)) {}

  const std::string& ClassName() const;
  // Get method definition by name. Zero if not exists
  std::shared_ptr<const MethodDefinition> GetMethodDefinition(
      const std::string& name) const;

  // Get field definition by name. NotFound if not exists
  TypeIdentifier GetFieldType(const std::string& name) const;
  const std::unordered_map<std::string, TypeIdentifier>& Fields() const;
  bool HasParent() const { return hasParent_; }
  std::string GetParentName() const { return parentName_; }

 private:
  std::string className_;
  std::shared_ptr<NameToMethodDefinitionMap> methods_;
  std::shared_ptr<NameToFieldTypeMap> fields_;
  bool hasParent_;
  std::string parentName_;
};

////////////////////////////////////////////////////////////////////////////////////

class MethodDefinition {
 public:
  using NameToVarTypeMap = std::unordered_map<std::string, TypeIdentifier>;
  using ArgumentsTypesList = std::vector<TypeIdentifier>;
  MethodDefinition(AccessModifiers accessModifier, std::string methodName,
                   TypeIdentifier returnType,
                   std::shared_ptr<NameToVarTypeMap> argumentTypes,
                   std::shared_ptr<ArgumentsTypesList> sortedArgumentsTypes,
                   std::shared_ptr<NameToVarTypeMap> localVariablesTypes)
      : accessModifier_(accessModifier),
        methodName_(std::move(methodName)),
        returnType_(std::move(returnType)),
        argumentTypes_(std::move(argumentTypes)),
        sortedArgumentsTypes_(std::move(sortedArgumentsTypes)),
        localVariableTypes_(std::move(localVariablesTypes)) {}

  AccessModifiers AccessModifier() const { return accessModifier_; }
  const std::string& MethodName() const { return methodName_; }
  TypeIdentifier ReturnType() const { return returnType_; }

  // Return NotFound in CTypeIdentifier if variable not found
  TypeIdentifier GetLocalVariableType(const std::string& name) const;
  TypeIdentifier GetArgumentType(const std::string& name) const;
  TypeIdentifier GetArgumentType(int index) const;
  TypeIdentifier GetVariableType(const std::string& name) const;
  int GetArgumentsNumber() const;

  std::shared_ptr<NameToVarTypeMap> LocalVariables() const;

 private:
  AccessModifiers accessModifier_;
  std::string methodName_;
  TypeIdentifier returnType_;
  std::shared_ptr<NameToVarTypeMap> argumentTypes_;
  std::shared_ptr<NameToVarTypeMap> localVariableTypes_;
  std::shared_ptr<ArgumentsTypesList> sortedArgumentsTypes_;
};
