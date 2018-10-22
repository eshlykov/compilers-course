#pragma once

#include <memory>

class Type;
class Identifier;

class CommaTypeIdentifier {
public:
    CommaTypeIdentifier(std::shared_ptr<Type> type, std::shared_ptr<Identifier> name) :
        type_{type}, name_{name} {
    }

private:
    std::shared_ptr<Type> type_ = {};
    std::shared_ptr<Identifier> name_ = {};
};
