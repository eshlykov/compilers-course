#pragma once

class Identifier;

class Type {
public:
    Type(Identifier* className) :
        className_(className) {
    };

public:
    Identifier* className_ = {};
};
