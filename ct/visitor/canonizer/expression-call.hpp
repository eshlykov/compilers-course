#pragma once

#include "../../../utils/ct.hpp"
#include <memory>
#include <vector>

namespace Ct {

    class ExpressionCall : public Statement {
    public:
        ExpressionCall(std::shared_ptr<Call> call);

        virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

        virtual std::shared_ptr<Statement> Build(const std::vector<std::shared_ptr<Expression>>& kids) override final;

    private:
        std::shared_ptr<Call> Call_;
    };

    inline ExpressionCall::ExpressionCall(std::shared_ptr<Call> call) :
        Call_(call) {
    }

    inline std::vector<std::shared_ptr<Expression>> ExpressionCall::Kids() {
        return Call_->Kids();
    }

    inline std::shared_ptr<Statement> ExpressionCall::Build(const std::vector<std::shared_ptr<Expression>>& kids) {
        return std::make_shared<Void>(Call_->Build(kids));
    }

}
