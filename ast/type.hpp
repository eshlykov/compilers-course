#pragma once

class Identifier;

class Type {
public:
    Type(std::shared_ptr<Identifier> className) :
        className_(className) {
    };

public:
    std::shared_ptr<Identifier> className_ = {};
};
