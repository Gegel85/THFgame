//
// Created by Gegel85 on 26/09/2019.
//

#include "PositionComponent.hpp"
#include "../Exceptions.hpp"

namespace TouhouFanGame::ECS::Components
{
	PositionComponent::PositionComponent(std::istream &stream) :
		Component("Position")
	{
		stream >> this->position.x >> this->position.y >> this->size.x >> this->size.y;
		if (stream.fail())
			throw InvalidSerializedString("Invalid PositionComponent");
	}

	PositionComponent::PositionComponent(sf::Vector2u size) :
		Component("Position"),
		size(size)
	{
	}

	void PositionComponent::serialize(std::ostream &stream) const
	{
		stream << this->position.x << " " << this->position.y << " " << this->size.x << " " << this->size.y;
	}
}