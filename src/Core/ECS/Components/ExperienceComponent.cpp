//
// Created by Gegel85 on 20/01/2020.
//

#include <iostream>
#include "ExperienceComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	ExperienceComponent::ExperienceComponent() :
		Component("Experience")
	{
	}

	ExperienceComponent::ExperienceComponent(std::istream &stream) :
		Component("Experience")
	{
		stream >> this->level >> this->exp;
	}

	void ExperienceComponent::serialize(std::ostream &stream) const
	{
		stream << this->level << " " << this->exp;
	}
}