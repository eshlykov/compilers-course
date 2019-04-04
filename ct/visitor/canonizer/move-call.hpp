#pragma once

#include "../../../utils/ct.hpp"
#include <memory>
#include <vector>

namespace Ct {

    class MoveCall : public Statement {
    public:
        MoveCall(std::shared_ptr<Temporary> destination, std::shared_ptr<Call> source);

        virtual void Accept(Visitor*) override final {
        }

        virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

        virtual std::shared_ptr<Statement> Build(const std::vector<std::shared_ptr<Expression>>& kids) override final;

    private:
        std::shared_ptr<Temporary> Destination_;
        std::shared_ptr<Call> Source_;
    };

    inline MoveCall::MoveCall(std::shared_ptr<Temporary> destination, std::shared_ptr<Call> source) :
        Destination_(destination), Source_(source) {
    }

    inline std::vector<std::shared_ptr<Expression>> MoveCall::Kids() {
        return Source_->Kids();
    }

    inline std::shared_ptr<Statement> MoveCall::Build(const std::vector<std::shared_ptr<Expression>>& kids) {
        return std::make_shared<Move>(Destination_, Source_->Build(kids));
    }

}
