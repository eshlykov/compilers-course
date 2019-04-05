#include "canonizer.hpp"

namespace Ct {

Canonizer::Canonizer() {}

void Canonizer::Visit(BinaryOperator* node) {}

void Canonizer::Visit(Call* node) {}

void Canonizer::Visit(ConditionalJump* node) {}

void Canonizer::Visit(Constant* node) {}

void Canonizer::Visit(ExpressionSequence* node) {}

void Canonizer::Visit(Jump* node) {}

void Canonizer::Visit(Label* node) {}

void Canonizer::Visit(Memory* node) {}

void Canonizer::Visit(Move* node) {}

void Canonizer::Visit(Name* node) {}

void Canonizer::Visit(StatementSequence* node) {}

void Canonizer::Visit(Temporary* node) {}

void Canonizer::Visit(Void* node) {}

}  // namespace Ct
