//
// Created by Gegel85 on 20/01/2020.
//

#include "ExperienceSystem.hpp"
#include "../Components/ExperienceComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	ExperienceSystem::ExperienceSystem(TouhouFanGame::ECS::Core &_parent) :
		System(_parent, "Experience", {})
	{
	}

	void ExperienceSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &exp = entity->getComponent("Experience").to<Components::ExperienceComponent>();

		while (exp.exp >= exp.level * EXP_NEEDED)
			exp.exp -= exp.level++ * EXP_NEEDED;
	}
}