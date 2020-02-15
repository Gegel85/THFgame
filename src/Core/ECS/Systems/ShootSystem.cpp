//
// Created by Gegel85 on 12/01/2020.
//

#include "ShootSystem.hpp"
#include "../Components/ShootComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	ShootSystem::ShootSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "Shoot", {})
	{
	}

	void ShootSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &shoot = entity->getComponent("Shoot").to<Components::ShootComponent>();

		if (shoot.shooting)
			shoot.handler->call<void>("attackDefault", &*entity, &this->_core, &shoot.resources, &shoot.map);
		shoot.handler->update();
	}
}