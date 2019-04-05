#include "label.hpp"

namespace Irt {

Label::Label(const Address& address) : address_{address} {}

void Label::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Irt
