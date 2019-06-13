#include <ast/visitor/symbol-table.hpp>

void PrintType(TypeIdentifieres type) {
  std::string string;
  switch (type) {
    case TypeIdentifieres::Int: {
      string = "int";
      break;
    }
    case TypeIdentifieres::Boolean: {
      string = "boolean";
      break;
    }
    case TypeIdentifieres::IntArray: {
      string = "array";
      break;
    }
    case TypeIdentifieres::NotFound: {
      string = "notFound";
      break;
    }
    case TypeIdentifieres::ClassId: {
      string = "classId";
      break;
    }
    default: {
      string = "other";
      break;
    }
  }
  std::cout << string << std::endl;
}

bool SymbolTable::AddClassDefinition(
    const std::string& name,
    std::shared_ptr<const ClassDefinition> classDefinition) {
  bool ok =
      classes_
          .insert(std::make_pair(
              name, std::shared_ptr<const ClassDefinition>(classDefinition)))
          .second;
  return ok;
}

std::shared_ptr<const ClassDefinition> SymbolTable::GetClassDefinition(
    const std::string& name) const {
  auto it = classes_.find(name);
  if (it == classes_.end()) {
    return nullptr;
  }
  return it->second;
}

std::shared_ptr<const MethodDefinition>
SymbolTable::SearchClassHierarchyForMethod(
    const std::string& methodName,
    std::shared_ptr<const ClassDefinition> baseClass) const {
  std::shared_ptr<const MethodDefinition> methodDefinition = nullptr;
  while (baseClass != nullptr) {
    methodDefinition = baseClass->GetMethodDefinition(methodName);
    if (methodDefinition != nullptr) {
      break;
    }
    baseClass = baseClass->HasParent()
                    ? GetClassDefinition(baseClass->GetParentName())
                    : nullptr;
  }
  return methodDefinition;
}

TypeIdentifier SymbolTable::SearchClassHierarchyForField(
    const std::string& fieldName,
    std::shared_ptr<const ClassDefinition> baseClass) const {
  TypeIdentifier fieldType(TypeIdentifieres::NotFound);
  while (baseClass != nullptr) {
    fieldType = baseClass->GetFieldType(fieldName);
    if (fieldType.Type() != TypeIdentifieres::NotFound) {
      break;
    }
    baseClass = baseClass->HasParent()
                    ? GetClassDefinition(baseClass->GetParentName())
                    : nullptr;
  }
  return fieldType;
}

//////////////////////////////////////////

const std::string& ClassDefinition::ClassName() const { return className_; }

std::shared_ptr<const MethodDefinition> ClassDefinition::GetMethodDefinition(
    const std::string& name) const {
  auto result = methods_->find(name);
  if (result != methods_->end()) {
    return result->second;
  }
  return nullptr;
}

TypeIdentifier ClassDefinition::GetFieldType(const std::string& name) const {
  auto result = fields_->find(name);
  if (result != fields_->end()) {
    return result->second;
  }
  return TypeIdentifier(TypeIdentifieres::NotFound);
}

const std::unordered_map<std::string, TypeIdentifier>& ClassDefinition::Fields()
    const {
  return *fields_;
}

////////////////////////////////////////////////////

TypeIdentifier MethodDefinition::GetLocalVariableType(
    const std::string& name) const {
  auto result = localVariableTypes_->find(name);
  if (result != localVariableTypes_->end()) {
    return result->second;
  }
  return TypeIdentifier(TypeIdentifieres::NotFound);
}

TypeIdentifier MethodDefinition::GetArgumentType(
    const std::string& name) const {
  auto result = argumentTypes_->find(name);
  if (result != argumentTypes_->end()) {
    return result->second;
  }
  return TypeIdentifier(TypeIdentifieres::NotFound);
}

TypeIdentifier MethodDefinition::GetArgumentType(int index) const {
  if (index < sortedArgumentsTypes_->size()) {
    return (*sortedArgumentsTypes_)[index];
  }
  return TypeIdentifier(TypeIdentifieres::NotFound);
}

TypeIdentifier MethodDefinition::GetVariableType(
    const std::string& name) const {
  TypeIdentifier type = GetLocalVariableType(name);
  if (type.Type() == TypeIdentifieres::NotFound) {
    type = GetArgumentType(name);
  }
  return type;
}

int MethodDefinition::GetArgumentsNumber() const {
  return sortedArgumentsTypes_->size();
}

std::shared_ptr<std::unordered_map<std::string, TypeIdentifier>>
MethodDefinition::LocalVariables() const {
  return localVariableTypes_;
}
