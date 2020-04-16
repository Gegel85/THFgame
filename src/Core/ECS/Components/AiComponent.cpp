//
// Created by Gegel85 on 16/04/2020.
//

#include "AiComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	AIComponent::AIComponent(std::istream &stream, Map &map, ECS::Core &core) :
		ControllableComponent(this->_ai, stream),
		_ai(map, core)
	{
		this->_ai.unserialize(stream);
	}

	AIComponent::AIComponent(const std::string &modulePath, float regularSpeed, float sprintSpeed, Map &map, ECS::Core &core) :
		ControllableComponent(this->_ai, regularSpeed, sprintSpeed),
		_ai(modulePath, map, core)
	{

	}

	void AIComponent::serialize(std::ostream &stream) const
	{
		ControllableComponent::serialize(stream);
		this->_ai.serialize(stream);
	}
}