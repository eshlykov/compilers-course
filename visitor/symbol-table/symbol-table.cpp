#include "symbol-table.hpp"

void SymbolTable::Visit(AssignmentByIndexStatement* node) {
}

void SymbolTable::Visit(AssignmentStatement* node) {
}

void SymbolTable::Visit(BinaryOperatorExpression* node) {
}

void SymbolTable::Visit(BooleanExpression* node) {
}

void SymbolTable::Visit(ClassBody* node) {
    auto& [className, classInfo] = currentClass_;

    for (auto& variable : node->variables_) {
        variable->Accept(this);
        auto& [variableName, variableInfo] = currentVariable_;
        classInfo.AddVariable(variableName, variableInfo);
        currentVariable_ = {};
    }

    for (auto& method : node->methods_) {
        method->Accept(this);
        auto& [methodName, methodInfo] = currentMethod_;
        classInfo.AddMethod(methodName, methodInfo);
        currentMethod_ = {};
    }
}

void SymbolTable::Visit(ClassDeclaration* node) {
    currentClass_ = std::make_pair(node->className_, ClassInfo{});

    auto& [className, classInfo] = currentClass_;
    if (classes_.find(className) != classes_.end()) {
        throw ClassRedefinition{"Class " + className + " has been already defined."};
    }

    classInfo.base_ = node->extendsForClass_;
    node->classBody_->Accept(this);
    classes_[className] = classInfo;

    currentClass_ = {};
}

void SymbolTable::Visit(ConditionStatement* node) {
}

void SymbolTable::Visit(IdentifierExpression* node) {
}

void SymbolTable::Visit(IndexExpression* node) {
}

void SymbolTable::Visit(IntArrayConstructorExpression* node) {
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
        methodInfo.AddVariable(variableName, variableInfo);
        currentVariable_ = {};
    }
}

void SymbolTable::Visit(MethodCallExpression* node) {
}

void SymbolTable::Visit(MethodDeclaration* node) {
    currentMethod_ = std::make_pair(node->methodName_, MethodInfo{});

    auto& [methodName, methodInfo] = currentMethod_;
    methodInfo.returnType_ = node->resultType_.get();

    for (auto& argument : node->argumentsList_) {
        argument->Accept(this);
        auto& [variableName, variableInfo] = currentVariable_;
        methodInfo.AddArgument(variableName, variableInfo);
        currentVariable_ = {};
    }

    node->methodBody_->Accept(this);
}

void SymbolTable::Visit(NotExpression* node) {
}

void SymbolTable::Visit(NumberExpression* node) {
}

void SymbolTable::Visit(PrimitiveType* node) {
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

void SymbolTable::Visit(UserTypeConstructorExpression* node) {
}

void SymbolTable::Visit(UserType* node) {
}

void SymbolTable::Visit(VarDeclaration* node) {
    currentVariable_ = std::make_pair(node->name_, VariableInfo{});

    auto& [variableName, variableInfo] = currentVariable_;
    variableInfo.type_ = node->type_.get();
}
