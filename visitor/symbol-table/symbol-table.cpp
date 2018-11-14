#include "symbol-table.hpp"

virtual void SymbolTable::Visit(AssignmentByIndexStatement* node) override final {
}

virtual void SymbolTable::Visit(AssignmentStatement* node) override final {
}

virtual void SymbolTable::Visit(BinaryOperatorExpression* node) override final {
}

virtual void SymbolTable::Visit(BooleanExpression* node) override final {
}

virtual void SymbolTable::Visit(ClassBody* node) override final {
    auto& [className, classInfo] = currentClass_;

    for (auto* variable : node->variables_) {
        variable->Accept(this);
        auto& [variableName, variableInfo] = currentVariable_;
        classInfo.AddVariable(variableName, variableInfo);
        currentVariable_ = {};
    }

    for (auto* method : node->methods_) {
        method->Accept(this);
        auto& [methodName, methodInfo] = currentMethod_;
        classInfo.AddMethod(methodName, methodInfo);
        currentMethod_ = {};
    }
}

virtual void SymbolTable::Visit(ClassDeclaration* node) override final {
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

virtual void SymbolTable::Visit(ConditionStatement* node) override final {
}

virtual void SymbolTable::Visit(IdentifierExpression* node) override final {
}

virtual void SymbolTable::Visit(IndexExpression* node) override final {
}

virtual void SymbolTable::Visit(IntArrayConstructorExpression* node) override final {
}

virtual void SymbolTable::Visit(LengthExpression* node) override final {
}

virtual void SymbolTable::Visit(LoopStatement* node) override final {
}

virtual void SymbolTable::Visit(MainClass* node) override final {
}

virtual void SymbolTable::Visit(MethodBody* node) override final {
    auto& [methodName, methodInfo] = currentMethod_;

    for (auto* variable : node->variables_) {
        variable->Accept(this);
        auto& [variableName, variableInfo] = currentVariable_;
        methodInfo.AddVariable(variableName, variableInfo);
        currentVariable_ = {};
    }
}

virtual void SymbolTable::Visit(MethodCallExpression* node) override final {
}

virtual void SymbolTable::Visit(MethodDeclaration* node) override final {
    currentMethod_ = std::make_pair(node->methodName_, MethodInfo{});

    auto& [methodName, methodInfo] = currentMethod_;
    methodInfo.returnType_ = node->resultType_;

    for (auto* argument : node->argumentsList_) {
        argument->Accept(this);
        auto& [variableName, variableInfo] = currentVariable_;
        methodInfo.AddArgument(variableName, variableInfo);
        currentVariable_ = {};
    }

    node->methodBody_->Accept(this);
}

virtual void SymbolTable::Visit(NotExpression* node) override final {
}

virtual void SymbolTable::Visit(NumberExpression* node) override final {
}

virtual void SymbolTable::Visit(PrimitiveType* node) override final {
}

virtual void SymbolTable::Visit(PrintStatement* node) override final {
}

virtual void SymbolTable::Visit(Program* node) override final {
    for (auto* classDeclaration : node->classDeclarations_) {
        classDeclaration->Accept(this);
    }
}

virtual void SymbolTable::Visit(ScopeStatement* node) override final {
}

virtual void SymbolTable::Visit(ThisExpression* node) override final {
}

virtual void SymbolTable::Visit(UserTypeConstructorExpression* node) override final {
}

virtual void SymbolTable::Visit(UserType* node) override final {
}

virtual void SymbolTable::Visit(VarDeclaration* node) override final {
    currentVariable_ = std::make_pair(node->name_, VariableInfo{});

    auto& [variableName, variableInfo] = currentVariable_;
    variableInfo.type_ = node->type_;
}

