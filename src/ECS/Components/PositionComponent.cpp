//
// Created by Gegel85 on 26/09/2019.
//

#include "PositionComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	PositionComponent::PositionComponent(sf::Vector2u size) :
		Component("Position"),
		size(size)
	{
	}

	void PositionComponent::serialize(std::ostream &) const
	{}

	void PositionComponent::unserialize(std::istream &)
	{}
}