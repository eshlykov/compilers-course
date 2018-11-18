#pragma once

#include "node.hpp"
#include <string>
#include <variant>

class Type : public Node {
public:
	Type(Location location, const std::string& className) :
		type_{className} {
        location_ = location;
    }
    
    Type(Location location, TypeKind typeKind) :
    	type_{typeKind} {
        location_ = location;
    }
	
	virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }
    
public:
	std::variant<TypeKind, std::string> type_;
};