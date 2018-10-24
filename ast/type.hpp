#pragma once

class Identifier;

class Type {
public:
    std::shared_ptr<Identifier> className_ = {};
};