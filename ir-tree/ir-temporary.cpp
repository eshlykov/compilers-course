#include "ir-temporary.hpp"

IrTemporary::IrTemporary(const std::string& temporary) :
    temporary_(temporary) {
}

void IrTemporary::Accept(IrVisitor* visitor) {

}
