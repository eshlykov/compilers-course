#include "in-frame-access.hpp"
#include "frame.hpp"

namespace Ct {

    InFrameAccess::InFrameAccess(int offset) :
        offset_{offset} {
    }

    std::shared_ptr<Expression> InFrameAccess::GetData() const {
        if (offset_ == 0) {
            return std::make_shared<Memory>(
                std::make_shared<Temporary>(Frame::FramePointer_)
            );
        } else {
            return std::make_shared<Memory>(
                std::make_shared<BinaryOperator>(
                    ArithmeticOperator::Plus,
                    std::make_shared<Temporary>(Frame::FramePointer_),
                    std::make_shared<Constant>(offset_)
                )
            );
        }
    }

}
