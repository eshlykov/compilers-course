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
    methodInfo.returnType_ = node->resultType_.get();

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

std::vector<CompileError> SymbolTable::GetErrorList() const {
    return errors;
}
