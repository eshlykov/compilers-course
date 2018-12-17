#pragma once

#include "../../../utils/ast.hpp"
#include "../../../utils/irt.hpp"
#include "../../../irt/frame/code-fragment.hpp"
#include "../../../irt/frame/frame.hpp"
#include "../../../irt/wrapper/comparison-operator-wrapper.hpp"
#include "../../../irt/wrapper/and-operator-wrapper.hpp"
#include "../../../irt/wrapper/expression-wrapper.hpp"
#include "../symbol-table/symbol-table.hpp"
#include "../visitor.hpp"
#include <cassert>
#include <memory>
#include <optional>

namespace Ast {

    class Translator : public Visitor {
    public:
        Translator();

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

        std::shared_ptr<Irt::CodeFragment> GetCodeFragment();

    private:
        std::optional<Irt::ArithmeticOperator> ToIrtArithmeticOperator(BinaryOperator binaryOperator);

        std::shared_ptr<Irt::Expression> Allocate(std::shared_ptr<Irt::Expression> wordsCount);

    private:
        std::shared_ptr<Irt::Wrapper> wrapper_;
        std::shared_ptr<Irt::Statement> statement_;
        std::shared_ptr<Irt::CodeFragment> codeFragment_;
        SymbolTable symbolTable_;
        std::string className_;
        std::string methodName_;
        enum class VariableContext {
            ClassVariable,
            MethodVariable,
            MethodArgument
        } variableContext_;
    };

}
