//
// Created by Gegel85 on 18/11/2019.
//

#include <iostream>
#include "NameComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	NameComponent::NameComponent(std::istream &stream) :
		Component("Name")
	{
		std::getline(stream, this->name, '\0');
	}

	NameComponent::NameComponent(const std::string &name) :
		Component("Name"),
		name(name)
	{}

	void NameComponent::serialize(std::ostream &stream) const
	{
		stream << this->name << '\0';
	}
}