#include "main-class.hpp"

MainClass::MainClass(Location location,
    const std::string& className,
    const std::string& argv,
    std::unique_ptr<Statement> mainBody) :
        className_{className},
        argv_{argv},
        mainBody_{std::move(mainBody)} {
    SetLocation(location);
}

void MainClass::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
