#include "../../ast.hpp"
#include "symbol-table.hpp"
#include <variant>

void SymbolTable::Visit(AssignmentByIndexStatement* node) {
    std::optional<VariableInfo> variable = TryLookUpVariable(node->array_, node->location_);
    if (variable.has_value()) {
        CompareTypes(variable->type_, TypeVariant(TypeKind::TK_IntArray), node->location_);
    }
    node->index_->Accept(this);
    CompareTypes(node->index_->type_, TypeVariant(TypeKind::TK_Int), node->index_->location_);
    node->expression_->Accept(this);
    CompareTypes(node->expression_->type_, TypeVariant(TypeKind::TK_Int), node->expression_->location_);
}

void SymbolTable::Visit(AssignmentStatement* node) {
    std::optional<VariableInfo> variable = TryLookUpVariable(node->variable_, node->location_);
    if (!variable.has_value()) {
        return;
    }
    node->expression_->Accept(this);
    CompareTypes(variable.value().type_, node->expression_->type_, node->expression_->location_);
}

void SymbolTable::Visit(BinaryOperatorExpression* node) {
    node->lhs_->Accept(this);
    node->rhs_->Accept(this);
    if (node->binaryOperator_ == BinaryOperator::BO_And) {
        CompareTypes(node->lhs_->type_, TypeVariant(TypeKind::TK_Boolean), node->lhs_->location_);
        CompareTypes(node->rhs_->type_, TypeVariant(TypeKind::TK_Boolean), node->rhs_->location_);
        node->type_ = TypeKind::TK_Boolean;
    } else {
        CompareTypes(node->lhs_->type_, TypeVariant(TypeKind::TK_Int), node->lhs_->location_);
        CompareTypes(node->rhs_->type_, TypeVariant(TypeKind::TK_Int), node->rhs_->location_);
        node->type_ = TypeKind::TK_Int;
    }
}

void SymbolTable::Visit(BooleanExpression* node) {
    node->type_ = TypeKind::TK_Boolean;
}

void SymbolTable::Visit(ClassBody* node) {
    auto& [className, classInfo] = currentClass_;

    for (auto& variable : node->variables_) {
        variable->Accept(this);
        auto& [variableName, variableInfo] = currentVariable_;
        try {
            classInfo.AddVariable(variableName, variableInfo, variable->location_);
        } catch (CompileError& error) {
            errors.push_back(error);
        }
        currentVariable_ = {};
    }

    for (auto& method : node->methods_) {
        method->Accept(this);
        auto& [methodName, methodInfo] = currentMethod_;
        try {
            classInfo.AddMethod(methodName, methodInfo, method->location_);
        } catch (CompileError& error) {
            errors.push_back(error);
        }
        currentMethod_ = {};
    }
}

void SymbolTable::Visit(ClassDeclaration* node) {
    currentClass_ = std::make_pair(node->className_, ClassInfo{});

    auto& [className, classInfo] = currentClass_;
    if (classes_.find(className) != classes_.end()) {
        errors.push_back(ClassRedefinition{"class '" + className + "' has been already defined", node->location_});
    }
    
    if (node->extendsForClass_.has_value()) {
        std::string base = *node->extendsForClass_;
        if (classes_.find(base) != classes_.end()) {
            errors.push_back(UndeclaredClass{"undefined class '" + base + "'", node->location_});
        }
        classInfo.base_ = base;
    }
    
    node->classBody_->Accept(this);
    classes_[className] = classInfo;

    currentClass_ = {};
}

void SymbolTable::Visit(ConditionStatement* node) {
    if (node->condition_->type_ != TypeVariant(TypeKind::TK_Boolean)) {
        errors.push_back(TypeMismatch{node->condition_->type_, TypeKind::TK_Boolean, node->condition_->location_});
    }
    node->ifStatement_->Accept(this);
    node->elseStatement_->Accept(this);
}

void SymbolTable::Visit(IdentifierExpression* node) {
    std::optional<VariableInfo> variable = TryLookUpVariable(node->name_, node->location_);
    if (variable.has_value()) {
        node->type_ = variable->type_;
    }
}

void SymbolTable::Visit(IndexExpression* node) {
    node->lhs_->Accept(this);
    CompareTypes(node->lhs_->type_, TypeVariant(TypeKind::TK_IntArray), node->lhs_->location_);
    node->rhs_->Accept(this);
    CompareTypes(node->rhs_->type_, TypeVariant(TypeKind::TK_Int), node->rhs_->location_);
}

void SymbolTable::Visit(IntArrayConstructorExpression* node) {
    node->type_ = TypeKind::TK_IntArray;
}

void SymbolTable::Visit(LengthExpression* node) {
}

void SymbolTable::Visit(LoopStatement* node) {
}

void SymbolTable::Visit(MainClass* node) {
}

void SymbolTable::Visit(MethodBody* node) {
    auto& [methodName, methodInfo] = currentMethod_;

    for (auto& variable : node->variables_) {
        variable->Accept(this);
        auto& [variableName, variableInfo] = currentVariable_;
        try {
            methodInfo.AddVariable(variableName, variableInfo, variable->location_);
        } catch (CompileError& error) {
            errors.push_back(error);
        }
        currentVariable_ = {};
    }
}

void SymbolTable::Visit(MethodCallExpression* node) {
}

void SymbolTable::Visit(MethodDeclaration* node) {
    currentMethod_ = std::make_pair(node->methodName_, MethodInfo{});

    auto& [methodName, methodInfo] = currentMethod_;
    methodInfo.returnType_ = node->resultType_->type_;

    for (auto& argument : node->argumentsList_) {
        argument->Accept(this);
        auto& [variableName, variableInfo] = currentVariable_;
        try {
            methodInfo.AddArgument(variableName, variableInfo, argument->location_);
        } catch (CompileError& error) {
            errors.push_back(error);
        }
        currentVariable_ = {};
    }

    node->methodBody_->Accept(this);
}

void SymbolTable::Visit(NotExpression* node) {
}

void SymbolTable::Visit(NumberExpression* node) {
    node->type_ = TypeKind::TK_Int;
}

void SymbolTable::Visit(PrintStatement* node) {
}

void SymbolTable::Visit(Program* node) {
    for (auto& classDeclaration : node->classDeclarations_) {
        classDeclaration->Accept(this);
    }
}

void SymbolTable::Visit(ScopeStatement* node) {
}

void SymbolTable::Visit(ThisExpression* node) {
}

void SymbolTable::Visit(Type* node) {
}

void SymbolTable::Visit(UserTypeConstructorExpression* node) {
    node->type_ = node->name_;
}

void SymbolTable::Visit(VarDeclaration* node) {
    currentVariable_ = std::make_pair(node->name_, VariableInfo{});

    auto& [variableName, variableInfo] = currentVariable_;
    variableInfo.type_ = node->type_->type_;
}

std::vector<CompileError> SymbolTable::GetErrorList() const {
    return errors;
}

void SymbolTable::CompareTypes(TypeVariant lhs, TypeVariant rhs, const Location& location) {
    if (lhs != rhs) {
        errors.push_back(TypeMismatch{lhs, rhs, location,});
    }
}

std::optional<VariableInfo> SymbolTable::TryLookUpVariable(const std::string& name, const Location& location) {
    if (currentClass_.second.variables_.find(name) != currentClass_.second.variables_.end()) {
        return currentClass_.second.variables_[name];
    }
    auto iter = find_if(currentMethod_.second.arguments_.begin(), currentMethod_.second.arguments_.end(), [&] (const auto& argument) {
        return argument.first == name;
    });
    if (iter != currentMethod_.second.arguments_.end()) {
        return iter->second;
    }
    if (currentMethod_.second.variables_.find(name) != currentMethod_.second.variables_.end()) {
        return currentMethod_.second.variables_[name];
    }
    errors.push_back(UndeclaredVariable{"undefined variable '" + name + "'", location});
    return {};
}