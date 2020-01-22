//
// Created by Gegel85 on 26/09/2019.
//

#include "PositionComponent.hpp"
#include "../Exceptions.hpp"

namespace TouhouFanGame::ECS::Components
{
	PositionComponent::PositionComponent(std::istream &stream) :
		Component("Position"),
		angle(0)
	{
		stream >> this->position.x >> this->position.y >> this->size.x >> this->size.y >> this->angle;
		if (stream.fail())
			throw InvalidSerializedString("Invalid PositionComponent");
	}

	PositionComponent::PositionComponent(Vector2u size) :
		Component("Position"),
		size(size),
		angle(0)
	{}

	void PositionComponent::serialize(std::ostream &stream) const
	{
		stream << this->position.x << " " << this->position.y << " " << this->size.x << " " << this->size.y << " " << this->angle;
	}
}