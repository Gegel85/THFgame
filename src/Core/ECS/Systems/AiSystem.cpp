//
// Created by Gegel85 on 16/04/2020.
//

#include "../Core.hpp"
#include "AiSystem.hpp"
#include "../Components/AiComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	AISystem::AISystem(Core &core) :
		ControllableSystem(core, "AI")
	{
	}

	void AISystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &ai = entity->getComponent(AI);

		ai.ai.setMe(entity);
		this->_updateEntity(entity, ai);
	}
}