//
// Created by Gegel85 on 16/04/2020.
//

#include "AiComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	AIComponent::AIComponent(std::istream &stream, Map &map, ECS::Core &core) :
		ControllableComponent("AI", this->ai, stream),
		ai(map, core)
	{
		this->ai.unserialize(stream);
	}

	AIComponent::AIComponent(const std::string &modulePath, float regularSpeed, float sprintSpeed, Map &map, ECS::Core &core) :
		ControllableComponent("AI", this->ai, regularSpeed, sprintSpeed),
		ai(modulePath, map, core)
	{
	}

	void AIComponent::serialize(std::ostream &stream) const
	{
		ControllableComponent::serialize(stream);
		stream << " ";
		this->ai.serialize(stream);
	}

	void AIComponent::setControllerModulePath(const std::string &path)
	{
		this->ai.changeModule(path);
	}
}