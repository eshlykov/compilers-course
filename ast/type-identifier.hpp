#pragma once

class Identifier;

class TypeIdentifier : Type {
public:
    TypeIdentifier(std::shared_ptr<Identifier> className) : className_(className) {};

public:
    std::shared_ptr<Identifier> className_ = {};
};
