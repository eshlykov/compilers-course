#include "symbol-table.hpp"
#include "../../utils/ast.hpp"
#include "../../utils/switcher.hpp"
#include "../../utils/compile-error/compile-errors.hpp"
#include <variant>

void SymbolTable::Visit(AssignmentByIndexStatement* node) {
    std::optional<VariableInfo> variable = TryLookUpVariable(currentClass_.second, node->array_, node->GetLocation(), false);
    if (variable.has_value()) {
        CompareTypes(variable->type_, TypeVariant(TypeKind::TK_IntArray), node->GetLocation());
    }
    node->index_->Accept(this);
    CompareTypes(node->index_->GetType(), TypeVariant(TypeKind::TK_Int), node->index_->GetLocation());
    node->expression_->Accept(this);
    CompareTypes(node->expression_->GetType(), TypeVariant(TypeKind::TK_Int), node->expression_->GetLocation());
}

void SymbolTable::Visit(AssignmentStatement* node) {
    std::optional<VariableInfo> variable = TryLookUpVariable(currentClass_.second, node->variable_, node->GetLocation(), false);
    if (!variable.has_value()) {
        return;
    }
    node->expression_->Accept(this);
    CompareTypes(node->expression_->GetType(), variable.value().type_, node->expression_->GetLocation());
}

void SymbolTable::Visit(BinaryOperatorExpression* node) {
    node->lhs_->Accept(this);
    node->rhs_->Accept(this);

    switch (node->binaryOperator_) {
    case BinaryOperator::BO_And:
        CompareTypes(node->lhs_->GetType(), TypeVariant(TypeKind::TK_Boolean), node->lhs_->GetLocation());
        CompareTypes(node->rhs_->GetType(), TypeVariant(TypeKind::TK_Boolean), node->rhs_->GetLocation());
        break;
    default:
        CompareTypes(node->lhs_->GetType(), TypeVariant(TypeKind::TK_Int), node->lhs_->GetLocation());
        CompareTypes(node->rhs_->GetType(), TypeVariant(TypeKind::TK_Int), node->rhs_->GetLocation());
    }

    switch (node->binaryOperator_) {
    case BinaryOperator::BO_And:
    case BinaryOperator::BO_Less:
        node->SetType(TypeKind::TK_Boolean);
        break;
    default:
        node->SetType(TypeKind::TK_Int);
    }
}

void SymbolTable::Visit(BooleanExpression* node) {
    node->SetType(TypeKind::TK_Boolean);
}

void SymbolTable::Visit(ClassBody* node) {
    for (auto& variable : node->variables_) {
        variable->Accept(this);
    }
    for (auto& method : node->methods_) {
        method->Accept(this);
    }
}

void SymbolTable::Visit(ClassDeclaration* node) {
    Switcher currentClass{currentClass_, {}};
    *currentClass = {node->className_, classes_.at(node->className_)};

    if (currentClass->second.GetBase().has_value()) {
        std::string baseClassName = currentClass->second.GetBase().value();
        if (CheckIfUndeclared(TypeVariant(baseClassName), node->GetLocation())) {
            classes_[node->className_].SetBase({});
            *currentClass = {node->className_, classes_.at(node->className_)};
        } else if (IsBaseOf(node->className_, baseClassName)) {
            errors.push_back(MutualInheritance{"classes '" + node->className_ + "' and '" + baseClassName + "' extend each other", node->GetLocation()});
            classes_[baseClassName].SetBase({});
        }
    }

    node->classBody_->Accept(this);
}

void SymbolTable::Visit(ConditionStatement* node) {
    node->condition_->Accept(this);
    CompareTypes(node->condition_->GetType(), TypeVariant(TypeKind::TK_Boolean), node->condition_->GetLocation());
    node->ifStatement_->Accept(this);
    node->elseStatement_->Accept(this);
}

void SymbolTable::Visit(IdentifierExpression* node) {
    std::optional<VariableInfo> variable = TryLookUpVariable(currentClass_.second, node->name_, node->GetLocation(), false);
    if (variable.has_value()) {
        node->SetType(variable->type_);
    }
}

void SymbolTable::Visit(IndexExpression* node) {
    node->lhs_->Accept(this);
    CompareTypes(node->lhs_->GetType(), TypeVariant(TypeKind::TK_IntArray), node->lhs_->GetLocation());
    node->rhs_->Accept(this);
    CompareTypes(node->rhs_->GetType(), TypeVariant(TypeKind::TK_Int), node->rhs_->GetLocation());
    node->SetType(TypeKind::TK_Int);
}

void SymbolTable::Visit(IntArrayConstructorExpression* node) {
    node->expression_->Accept(this);
    CompareTypes(node->expression_->GetType(), TypeVariant(TypeKind::TK_Int), node->expression_->GetLocation());
    node->SetType(TypeKind::TK_IntArray);
}

void SymbolTable::Visit(LengthExpression* node) {
    node->expression_->Accept(this);
    CompareTypes(node->expression_->GetType(), TypeVariant(TypeKind::TK_IntArray), node->expression_->GetLocation());
    node->SetType(TypeKind::TK_Int);
}

void SymbolTable::Visit(LoopStatement* node) {
    node->condition_->Accept(this);
    CompareTypes(node->condition_->GetType(), TypeVariant(TypeKind::TK_Boolean), node->condition_->GetLocation());
    node->statement_->Accept(this);
}

void SymbolTable::Visit(MainClass* node) {
    // Все сделано в ForwardVisit
    node->mainBody_->Accept(this);
}

void SymbolTable::Visit(MethodBody* node) {
    for (auto& variable : node->variables_) {
        variable->Accept(this);
    }
    for (auto& statement : node->statements_) {
        statement->Accept(this);
    }
    node->returnExpression_->Accept(this);
    CompareTypes(node->returnExpression_->GetType(), currentMethod_.second.GetReturnType(), node->returnExpression_->GetLocation());
}

void SymbolTable::Visit(MethodCallExpression* node) {
    node->expression_->Accept(this);
    std::string typeName;
    try {
        typeName = std::get<std::string>(node->expression_->GetType());
        if (classes_.find(typeName) == classes_.end()) {
            return;
        }
    } catch (const std::bad_variant_access&) {
        errors.push_back(TypesMismatch{"primitive types do not have any methods", node->expression_->GetLocation()});
        return;
    }

    std::optional<MethodInfo> method = TryLookUpMethod(classes_.at(typeName), node->methodName_, node->GetLocation());
    if (!method.has_value()) {
        return;
    }

    int expectedCount = method->GetArguments().size();
    int givenCount = node->argumentsList_.size();
    if (expectedCount != givenCount) {
        errors.push_back(ArgumentsCountMismatch{"method '" + node->methodName_ + "' expects to be given " + std::to_string(expectedCount) +
            " arguments, but it is given " + std::to_string(givenCount) + " instead", node->GetLocation()});
    }

    for (int i = 0; i < givenCount; ++i) {
        auto& argument = node->argumentsList_[i];
        argument->Accept(this);
        if (i < expectedCount) {
            CompareTypes(argument->GetType(), method->GetArguments()[i].second.type_, argument->GetLocation());
        }
    }

    node->SetType(method->GetReturnType());
}

void SymbolTable::Visit(MethodDeclaration* node) {
    Switcher currentMethod{currentMethod_, {}};
    *currentMethod = {node->methodName_, currentClass_.second.GetMethods().at(node->methodName_)};
    node->resultType_->Accept(this);
    for (auto& argument : node->argumentsList_) {
        argument->Accept(this);
    }
    node->methodBody_->Accept(this);
}

void SymbolTable::Visit(NotExpression* node) {
    node->expression_->Accept(this);
    CompareTypes(node->expression_->GetType(), TypeVariant(TypeKind::TK_Boolean), node->expression_->GetLocation());
    node->SetType(TypeKind::TK_Boolean);
}

void SymbolTable::Visit(NumberExpression* node) {
    node->SetType(TypeKind::TK_Int);
}

void SymbolTable::Visit(PrintStatement* node) {
    node->expression_->Accept(this);
    CompareTypes(node->expression_->GetType(), TypeVariant(TypeKind::TK_Int), node->expression_->GetLocation());
}

void SymbolTable::Visit(Program* node) {
    ForwardVisit(node->mainClass_.get());
    for (auto& classDeclaration : node->classDeclarations_) {
        ForwardVisit(classDeclaration.get());
    }

    node->mainClass_->Accept(this);
    for (auto& classDeclaration : node->classDeclarations_) {
        classDeclaration->Accept(this);
    }
}

void SymbolTable::Visit(ScopeStatement* node) {
    for (auto& statement : node->statements_) {
        statement->Accept(this);
    }
}

void SymbolTable::Visit(ThisExpression* node) {
    node->SetType(currentClass_.first);
}

void SymbolTable::Visit(Type* node) {
    CheckIfUndeclared(node->type_, node->GetLocation());
}

void SymbolTable::Visit(UserTypeConstructorExpression* node) {
    CheckIfUndeclared(TypeVariant(node->name_), node->GetLocation());
    node->SetType(node->name_);
}

void SymbolTable::Visit(VarDeclaration* node) {
     node->type_->Accept(this);
}

void SymbolTable::ForwardVisit(MainClass* node) {
    // Делать ничего не нужно, так как класс нельзя использовать.
    // Например, будем считать, что метод main нельзя вызвать (даже в наследниках этого класса), поэтому не сохраняем.
    // Аргумент main'а не используется.
    // Единственное, от чего надо защититься, - переопределение класса
    classes_[node->className_] = {};
}

void SymbolTable::ForwardVisit(ClassDeclaration* node) {
    Switcher currentClass{currentClass_, {}};
    *currentClass = {node->className_, ClassInfo{}};

    auto& [className, classInfo] = *currentClass;
    if (classes_.find(className) != classes_.end()) {
        errors.push_back(ClassRedefinition{"class '" + className + "' has been already defined", node->GetLocation()});
    }

    if (node->extendsForClass_.has_value() && node->extendsForClass_.value() == node->className_) {
        errors.push_back(SelfInheritance{"class '" + className + "' inherits itself", node->GetLocation()});
    } else if (node->extendsForClass_.has_value()) {
        classInfo.SetBase(node->extendsForClass_.value());
    }

    ForwardVisit(node->classBody_.get());
    classes_[className] = classInfo;
}

void SymbolTable::ForwardVisit(ClassBody* node) {
    auto& [className, classInfo] = currentClass_;

    for (auto& variable : node->variables_) {
        ForwardVisit(variable.get());
        Switcher currentVariable{currentVariable_, {}};
        auto& [variableName, variableInfo] = *currentVariable;
        try {
            classInfo.AddVariable(variableName, variableInfo, variable->GetLocation());
        } catch (CompileError& error) {
            errors.push_back(error);
        }
    }

    for (auto& method : node->methods_) {
        ForwardVisit(method.get());
        Switcher currentMethod{currentMethod_, {}};
        auto& [methodName, methodInfo] = *currentMethod;
        try {
            classInfo.AddMethod(methodName, methodInfo, method->GetLocation());
        } catch (CompileError& error) {
            errors.push_back(error);
        }
    }
}

void SymbolTable::ForwardVisit(VarDeclaration* node) {
    currentVariable_ = {node->name_, VariableInfo{}};

    auto& [variableName, variableInfo] = currentVariable_;
    variableInfo.type_ = node->type_->type_;
}

void SymbolTable::ForwardVisit(MethodDeclaration* node) {
    currentMethod_ = {node->methodName_, MethodInfo{}};

    auto& [methodName, methodInfo] = currentMethod_;
    methodInfo.SetReturnType(node->resultType_->type_);

    for (auto& argument : node->argumentsList_) {
        ForwardVisit(argument.get());
        Switcher currentVariable{currentVariable_, {}};
        auto& [variableName, variableInfo] = *currentVariable;
        try {
            methodInfo.AddArgument(variableName, variableInfo, argument->GetLocation());
        } catch (CompileError& error) {
            errors.push_back(error);
        }
    }

    ForwardVisit(node->methodBody_.get());
}

void SymbolTable::ForwardVisit(MethodBody* node) {
    auto& [methodName, methodInfo] = currentMethod_;

    for (auto& variable : node->variables_) {
        ForwardVisit(variable.get());
        Switcher currentVariable{currentVariable_, {}};
        auto& [variableName, variableInfo] = *currentVariable;
        try {
            methodInfo.AddVariable(variableName, variableInfo, variable->GetLocation());
        } catch (CompileError& error) {
            errors.push_back(error);
        }
    }
}

std::vector<CompileError> SymbolTable::GetErrorList() const {
    return errors;
}

void SymbolTable::CompareTypes(TypeVariant lhs, TypeVariant rhs, const Location& location) {
    if (lhs == rhs) {
        return;
    }
    try {
        std::string derivedClassName = std::get<std::string>(lhs);
        std::string baseClassName = std::get<std::string>(rhs);
        if (IsBaseOf(baseClassName, derivedClassName)) {
            return;
        }
    } catch (const std::bad_variant_access&) {
    }
    errors.push_back(TypesMismatch{lhs, rhs, location});
}

bool SymbolTable::IsBaseOf(const std::string& baseClassName, const std::string& derivedClassName) const {
    ClassInfo derivedClass = classes_.at(derivedClassName);
    if (!derivedClass.GetBase().has_value()) {
        return false;
    }
    std::string derivedClassBaseName = derivedClass.GetBase().value();
    if (baseClassName == derivedClassBaseName) {
        return true;
    }
    return IsBaseOf(baseClassName, derivedClassBaseName);
}

std::optional<VariableInfo> SymbolTable::TryLookUpVariable(const ClassInfo& currentClass, const std::string& name, const Location& location, bool inBaseClass) {
    if (!inBaseClass) {
        if (currentMethod_.second.GetVariables().find(name) != currentMethod_.second.GetVariables().end()) {
            return currentMethod_.second.GetVariables().at(name);
        }
        auto iter = find_if(currentMethod_.second.GetArguments().begin(), currentMethod_.second.GetArguments().end(), [&] (const auto& argument) {
            return argument.first == name;
        });
        if (iter != currentMethod_.second.GetArguments().end()) {
            return iter->second;
        }
    }
    if (currentClass.GetVariables().find(name) != currentClass.GetVariables().end()) {
        return currentClass.GetVariables().at(name);
    }
    if (currentClass.GetBase().has_value()) {
        return TryLookUpVariable(classes_.at(currentClass.GetBase().value()), name, location, true);
    }
    errors.push_back(UndeclaredVariable{"undeclared variable '" + name + "'", location});
    return {};
}

std::optional<MethodInfo> SymbolTable::TryLookUpMethod(const ClassInfo& currentClass, const std::string& name, const Location& location) {
    if (currentClass.GetMethods().find(name) != currentClass.GetMethods().end()) {
        return currentClass.GetMethods().at(name);
    }
    if (currentClass.GetBase().has_value()) {
        return TryLookUpMethod(classes_.at(currentClass.GetBase().value()), name, location);
    }
    errors.push_back(UndeclaredMethod{"undeclared method '" + name + "'", location});
    return {};
}

bool SymbolTable::CheckIfUndeclared(TypeVariant type, const Location& location) {
    try {
        std::string typeName = std::get<std::string>(type);
        if (classes_.find(typeName) == classes_.end()) {
            errors.push_back(UndeclaredClass{"undeclared class '" + typeName + "'", location});
            return true;
        }
    } catch (const std::bad_variant_access&) {
    }
    return false;
}
