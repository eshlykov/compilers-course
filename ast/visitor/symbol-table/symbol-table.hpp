#pragma once

#include "../../../utils/ast.hpp"
#include "../../../utils/compile-error/compile-error.hpp"
#include "../visitor.hpp"
#include "class-info.hpp"
#include "method-info.hpp"
#include "variable-info.hpp"
#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Ast {

    class SymbolTable : public Visitor {
        using TypeVariant = std::variant<TypeKind, std::string>;

    public:
        virtual ~SymbolTable() = default;

        virtual void Visit(AssignmentByIndexStatement* node) override final;

        virtual void Visit(AssignmentStatement* node) override final;

        virtual void Visit(BinaryOperatorExpression* node) override final;

        virtual void Visit(BooleanExpression* node) override final;

        virtual void Visit(ClassBody* node) override final;

        virtual void Visit(ClassDeclaration* node) override final;

        virtual void Visit(ConditionStatement* node) override final;

        virtual void Visit(IdentifierExpression* node) override final;

        virtual void Visit(IndexExpression* node) override final;

        virtual void Visit(IntArrayConstructorExpression* node) override final;

        virtual void Visit(LengthExpression* node) override final;

        virtual void Visit(LoopStatement* node) override final;

        virtual void Visit(MainClass* node) override final;

        virtual void Visit(MethodBody* node) override final;

        virtual void Visit(MethodCallExpression* node) override final;

        virtual void Visit(MethodDeclaration* node) override final;

        virtual void Visit(NotExpression* node) override final;

        virtual void Visit(NumberExpression* node) override final;

        virtual void Visit(PrintStatement* node) override final;

        virtual void Visit(Program* node) override final;

        virtual void Visit(ScopeStatement* node) override final;

        virtual void Visit(ThisExpression* node) override final;

        virtual void Visit(Type* node) override final;

        virtual void Visit(UserTypeConstructorExpression* node) override final;

        virtual void Visit(VarDeclaration* node) override final;

        std::vector<CompileError> GetErrorList() const;

        const std::unordered_map<std::string, ClassInfo>& GetClasses() const;

        int GetVariableOffset(const std::string& className, const std::string& variableName);

    private:
        void ForwardVisit(MainClass* node);

        void ForwardVisit(ClassDeclaration* node);

        void ForwardVisit(ClassBody* node);

        void ForwardVisit(VarDeclaration* node);

        void ForwardVisit(MethodDeclaration* node);

        void ForwardVisit(MethodBody* node);

        void CompareTypes(TypeVariant lhs, TypeVariant rhs, const Location& location);

        bool IsBaseOf(const std::string& baseClassName, const std::string& derivedClassName) const;

        std::optional<VariableInfo> TryLookUpVariable(const ClassInfo& currentClass, const std::string& name, const Location& location, bool inBaseClass);

        std::optional<MethodInfo> TryLookUpMethod(const ClassInfo& currentClass, const std::string& name, const Location& location);

        bool CheckIfUndeclared(TypeVariant type, const Location& location);

        void UpdateVariableOffsets(const std::string& name);

    private:
        std::unordered_map<std::string, ClassInfo> classes_;
        std::pair<std::string, VariableInfo> currentVariable_;
        std::pair<std::string, MethodInfo> currentMethod_;
        std::pair<std::string, ClassInfo> currentClass_;
        std::vector<CompileError> errors_;
    };

}
