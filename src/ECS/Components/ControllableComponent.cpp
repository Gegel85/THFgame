//
// Created by Gegel85 on 28/09/2019.
//

#include "ControllableComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	ControllableComponent::ControllableComponent(TouhouFanGame::Input &input, float regularSpeed, float sprintSpeed) :
		Component("Controllable"),
		input(input),
		regularSpeed(regularSpeed),
		sprintSpeed(sprintSpeed)
	{}

	void ControllableComponent::serialize(std::ostream &) const
	{}

	void ControllableComponent::unserialize(std::istream &)
	{}
}