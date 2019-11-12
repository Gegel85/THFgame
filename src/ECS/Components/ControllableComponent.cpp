//
// Created by Gegel85 on 28/09/2019.
//

#include "ControllableComponent.hpp"
#include "../Exceptions.hpp"

namespace TouhouFanGame::ECS::Components
{
	ControllableComponent::ControllableComponent(TouhouFanGame::Input &input, std::istream &stream) :
		Component("Controllable"),
		input(input)
	{
		stream >> regularSpeed >> sprintSpeed;
		if (stream.fail())
			throw InvalidSerializedString("Invalid ControllableComponent");
	}

	ControllableComponent::ControllableComponent(TouhouFanGame::Input &input, float regularSpeed, float sprintSpeed) :
		Component("Controllable"),
		input(input),
		regularSpeed(regularSpeed),
		sprintSpeed(sprintSpeed)
	{}

	void ControllableComponent::serialize(std::ostream &stream) const
	{
		stream << regularSpeed << " " << sprintSpeed;
	}
}