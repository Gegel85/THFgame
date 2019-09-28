//
// Created by Gegel85 on 28/09/2019.
//

#include "MovableComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	MovableComponent::MovableComponent() :
		Component("Movable")
	{}

	void MovableComponent::serialize(std::ostream &) const
	{}

	void MovableComponent::unserialize(std::istream &)
	{}
}