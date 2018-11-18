#include "../../ast.hpp"
#include "symbol-table.hpp"
#include <variant>

void SymbolTable::Visit(AssignmentByIndexStatement* node) {
    std::optional<VariableInfo> variable = TryLookUpVariable(currentClass_.second, node->array_, node->location_, false);
    if (variable.has_value()) {
        CompareTypes(variable->type_, TypeVariant(TypeKind::TK_IntArray), node->location_);
    }
    node->index_->Accept(this);
    CompareTypes(node->index_->type_, TypeVariant(TypeKind::TK_Int), node->index_->location_);
    node->expression_->Accept(this);
    CompareTypes(node->expression_->type_, TypeVariant(TypeKind::TK_Int), node->expression_->location_);
}

void SymbolTable::Visit(AssignmentStatement* node) {
    std::optional<VariableInfo> variable = TryLookUpVariable(currentClass_.second, node->variable_, node->location_, false);
    if (!variable.has_value()) {
        return;
    }
    node->expression_->Accept(this);
    CompareTypes(node->expression_->type_, variable.value().type_, node->expression_->location_);
}

void SymbolTable::Visit(BinaryOperatorExpression* node) {
    node->lhs_->Accept(this);
    node->rhs_->Accept(this);

    switch (node->binaryOperator_) {
    case BinaryOperator::BO_And:
        CompareTypes(node->lhs_->type_, TypeVariant(TypeKind::TK_Boolean), node->lhs_->location_);
        CompareTypes(node->rhs_->type_, TypeVariant(TypeKind::TK_Boolean), node->rhs_->location_);
        break;
    default:
        CompareTypes(node->lhs_->type_, TypeVariant(TypeKind::TK_Int), node->lhs_->location_);
        CompareTypes(node->rhs_->type_, TypeVariant(TypeKind::TK_Int), node->rhs_->location_);
    }

    switch (node->binaryOperator_) {
    case BinaryOperator::BO_And:
    case BinaryOperator::BO_Less:
        node->type_ = TypeKind::TK_Boolean;
        break;
    default:
        node->type_ = TypeKind::TK_Int;
    }
}

void SymbolTable::Visit(BooleanExpression* node) {
    node->type_ = TypeKind::TK_Boolean;
}

void SymbolTable::Visit(ClassBody* node) {
    // Переменные обработаны в ForwardVisit
    for (auto& method : node->methods_) {
        method->Accept(this);
    }
}

void SymbolTable::Visit(ClassDeclaration* node) {
    currentClass_ = {node->className_, classes_.at(node->className_)};

    if (currentClass_.second.base_.has_value()) {
        std::string baseClassName = currentClass_.second.base_.value();
        if (classes_.find(baseClassName) == classes_.end()) {
            errors.push_back(UndeclaredClass{"undeclared class '" + baseClassName + "'", node->location_});
            classes_[node->className_].base_ = {};
            currentClass_ = {node->className_, classes_.at(node->className_)};
        } else if (IsBaseOf(node->className_, baseClassName)) {
            errors.push_back(MutualInheritance{"classes '" + node->className_ + "' and '" + baseClassName + "' extend each other", node->location_});
            classes_[baseClassName].base_ = {};
        }
    }

    node->classBody_->Accept(this);

    currentClass_ = {};
}

void SymbolTable::Visit(ConditionStatement* node) {
    node->condition_->Accept(this);
    CompareTypes(node->condition_->type_, TypeVariant(TypeKind::TK_Boolean), node->condition_->location_);
    node->ifStatement_->Accept(this);
    node->elseStatement_->Accept(this);
}

void SymbolTable::Visit(IdentifierExpression* node) {
    std::optional<VariableInfo> variable = TryLookUpVariable(currentClass_.second, node->name_, node->location_, false);
    if (variable.has_value()) {
        node->type_ = variable->type_;
    }
}

void SymbolTable::Visit(IndexExpression* node) {
    node->lhs_->Accept(this);
    CompareTypes(node->lhs_->type_, TypeVariant(TypeKind::TK_IntArray), node->lhs_->location_);
    node->rhs_->Accept(this);
    CompareTypes(node->rhs_->type_, TypeVariant(TypeKind::TK_Int), node->rhs_->location_);
    node->type_ = TypeKind::TK_Int;
}

void SymbolTable::Visit(IntArrayConstructorExpression* node) {
    node->type_ = TypeKind::TK_IntArray;
}

void SymbolTable::Visit(LengthExpression* node) {
    node->expression_->Accept(this);
    CompareTypes(node->expression_->type_, TypeVariant(TypeKind::TK_IntArray), node->expression_->location_);
    node->type_ = TypeKind::TK_Int;
}

void SymbolTable::Visit(LoopStatement* node) {
    node->condition_->Accept(this);
    CompareTypes(node->condition_->type_, TypeVariant(TypeKind::TK_Boolean), node->condition_->location_);
    node->statement_->Accept(this);
}

void SymbolTable::Visit(MainClass* node) {
    // Все сделано в ForwardVisit
}

void SymbolTable::Visit(MethodBody* node) {
    for (auto& statement : node->statements_) {
        statement->Accept(this);
    }
    node->returnExpression_->Accept(this);
    CompareTypes(node->returnExpression_->type_, currentMethod_.second.returnType_, node->returnExpression_->location_);
}

void SymbolTable::Visit(MethodCallExpression* node) {
    node->expression_->Accept(this);
    std::string typeName;
    try {
        typeName = std::get<std::string>(node->expression_->type_);
    } catch (const std::bad_variant_access&) {
        errors.push_back(TypesMismatch{"primitive types do not have any methods", node->expression_->location_});
        return;
    }

    std::optional<MethodInfo> method = TryLookUpMethod(classes_.at(typeName), node->methodName_, node->location_);
    if (!method.has_value()) {
        errors.push_back(UndeclaredMethod{"undeclared method '" + node->methodName_ + "'", node->location_});
        return;
    }

    if (node->argumentsList_.size() != method->arguments_.size()) {
        errors.push_back(ArgumentsCountMismatch{"method '" + node->methodName_ + "' expects to be given " + std::to_string(method->arguments_.size()) +
            " arguments, but it is given " + std::to_string(node->argumentsList_.size()) + " insted", node->location_});
    }

    for (int i = 0; i < node->argumentsList_.size(); ++i) {
        auto& argument = node->argumentsList_[i];
        argument->Accept(this);
        CompareTypes(argument->type_, method->arguments_[i].second.type_, argument->location_);
    }

    node->type_ = method->returnType_;
}

void SymbolTable::Visit(MethodDeclaration* node) {
    currentMethod_ = {node->methodName_, currentClass_.second.methods_.at(node->methodName_)};
    node->methodBody_->Accept(this);
    currentMethod_ = {};
}

void SymbolTable::Visit(NotExpression* node) {
    node->expression_->Accept(this);
    CompareTypes(node->expression_->type_, TypeVariant(TypeKind::TK_Boolean), node->expression_->location_);
    node->type_ = TypeKind::TK_Boolean;
}

void SymbolTable::Visit(NumberExpression* node) {
    node->type_ = TypeKind::TK_Int;
}

void SymbolTable::Visit(PrintStatement* node) {
    // Будем считать, что у нас принт может вывести все типы (значение, список элементов массива или имя класса)
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
    node->type_ = currentClass_.first;
}

void SymbolTable::Visit(Type* node) {
    // Ничего делать не надо
}

void SymbolTable::Visit(UserTypeConstructorExpression* node) {
    if (classes_.find(node->name_) == classes_.end()) {
        errors.push_back(UndeclaredClass{"undeclared class '" + node->name_ + "'", node->location_});
    }
    node->type_ = node->name_;
}

void SymbolTable::Visit(VarDeclaration* node) {
    // Все уже сделали в ForwardVisit
}

void SymbolTable::ForwardVisit(MainClass* node) {
    // Делать ничего не нужно, так как класс нельзя использовать.
    // Например, будем считать, что метод main нельзя вызвать (даже в наследниках этого класса), поэтому не сохраняем.
    // Аргумент main'а не используется.
    // Единственное, от чего надо защититься, - переопределение класса
    classes_[node->className_] = {};
}

void SymbolTable::ForwardVisit(ClassDeclaration* node) {
    currentClass_ = {node->className_, ClassInfo{}};

    auto& [className, classInfo] = currentClass_;
    if (classes_.find(className) != classes_.end()) {
        errors.push_back(ClassRedefinition{"class '" + className + "' has been already defined", node->location_});
    }

    if (node->extendsForClass_.has_value() && node->extendsForClass_.value() == node->className_) {
        errors.push_back(SelfInheritance{"class + '" + className + "' inherits itself", node->location_});
    } else {
        classInfo.base_ = node->extendsForClass_;
    }

    ForwardVisit(node->classBody_.get());
    classes_[className] = classInfo;

    currentClass_ = {};
}

void SymbolTable::ForwardVisit(ClassBody* node) {
    auto& [className, classInfo] = currentClass_;

    for (auto& variable : node->variables_) {
        ForwardVisit(variable.get());
        auto& [variableName, variableInfo] = currentVariable_;
        try {
            classInfo.AddVariable(variableName, variableInfo, variable->location_);
        } catch (CompileError& error) {
            errors.push_back(error);
        }
        currentVariable_ = {};
    }

    for (auto& method : node->methods_) {
        ForwardVisit(method.get());
        auto& [methodName, methodInfo] = currentMethod_;
        try {
            classInfo.AddMethod(methodName, methodInfo, method->location_);
        } catch (CompileError& error) {
            errors.push_back(error);
        }
        currentMethod_ = {};
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
    methodInfo.returnType_ = node->resultType_->type_;

    for (auto& argument : node->argumentsList_) {
        ForwardVisit(argument.get());
        auto& [variableName, variableInfo] = currentVariable_;
        try {
            methodInfo.AddArgument(variableName, variableInfo, argument->location_);
        } catch (CompileError& error) {
            errors.push_back(error);
        }
        currentVariable_ = {};
    }

    ForwardVisit(node->methodBody_.get());
}

void SymbolTable::ForwardVisit(MethodBody* node) {
    auto& [methodName, methodInfo] = currentMethod_;

    for (auto& variable : node->variables_) {
        ForwardVisit(variable.get());
        auto& [variableName, variableInfo] = currentVariable_;
        try {
            methodInfo.AddVariable(variableName, variableInfo, variable->location_);
        } catch (CompileError& error) {
            errors.push_back(error);
        }
        currentVariable_ = {};
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
    errors.push_back(TypesMismatch{lhs, rhs, location,});
}

bool SymbolTable::IsBaseOf(const std::string& baseClassName, const std::string& derivedClassName) const {
    ClassInfo derivedClass = classes_.at(derivedClassName);
    if (!derivedClass.base_.has_value()) {
        return false;
    }
    std::string derivedClassBaseName = derivedClass.base_.value();
    if (baseClassName == derivedClassBaseName) {
        return true;
    }
    return IsBaseOf(baseClassName, derivedClassBaseName);
}

std::optional<VariableInfo> SymbolTable::TryLookUpVariable(const ClassInfo& currentClass, const std::string& name, const Location& location, bool inBaseClass) {
    if (!inBaseClass) {
        if (currentMethod_.second.variables_.find(name) != currentMethod_.second.variables_.end()) {
            return currentMethod_.second.variables_.at(name);
        }
        auto iter = find_if(currentMethod_.second.arguments_.begin(), currentMethod_.second.arguments_.end(), [&] (const auto& argument) {
            return argument.first == name;
        });
        if (iter != currentMethod_.second.arguments_.end()) {
            return iter->second;
        }
    }
    if (currentClass.variables_.find(name) != currentClass.variables_.end()) {
        return currentClass.variables_.at(name);
    }
    if (currentClass.base_.has_value()) {
        return TryLookUpVariable(classes_.at(currentClass.base_.value()), name, location, true);
    }
    errors.push_back(UndeclaredVariable{"undeclared variable '" + name + "'", location});
    return {};
}

std::optional<MethodInfo> SymbolTable::TryLookUpMethod(const ClassInfo& currentClass, const std::string& name, const Location& location) {
    if (currentClass.methods_.find(name) != currentClass.methods_.end()) {
        return currentClass.methods_.at(name);
    }
    if (currentClass.base_.has_value()) {
        return TryLookUpMethod(classes_.at(currentClass.base_.value()), name, location);
    }
    errors.push_back(UndeclaredMethod{"undeclared method '" + name + "'", location});
    return {};
}
