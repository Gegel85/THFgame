//
// Created by Gegel85 on 28/09/2019.
//

#include <iostream>
#include "MovableComponent.hpp"
#include "../Exceptions.hpp"

namespace TouhouFanGame::ECS::Components
{
	MovableComponent::MovableComponent(std::istream &stream) :
		Component("Movable")
	{
		stream >> this->speed >> this->angleDir;
		if (stream.fail())
			throw InvalidSerializedString("Invalid MovableComponent");
	}

	MovableComponent::MovableComponent() :
		Component("Movable")
	{}

	void MovableComponent::serialize(std::ostream &stream) const
	{
		stream << this->speed << " " << this->angleDir;
	}
}