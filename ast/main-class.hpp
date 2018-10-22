#pragma once

#include <memory>

class Identifier;
class Statement;

class MainClass {
public:
    MainClass(std::shared_ptr<Identifier> className, std::shared_ptr<Identifier> mainArgumentName, std::shared_ptr<Statement> mainBody) :
        className_{className}, mainArgumentName_{mainArgumentName}, mainBody_{mainBody} {
    }

public:
    std::shared_ptr<Identifier> className_ = {};
    std::shared_ptr<Identifier> mainArgumentName_ = {};
    std::shared_ptr<Statement> mainBody_ = {};
};
