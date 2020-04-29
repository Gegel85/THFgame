//
// Created by Gegel85 on 12/01/2020.
//

#include <iostream>
#include "ShootSystem.hpp"
#include "../Components/ShootComponent.hpp"
#include "../../Utils/Utils.hpp"

namespace TouhouFanGame::ECS::Systems
{
	ShootSystem::ShootSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "Shoot", {})
	{
	}

	void ShootSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &shoot = entity->getComponent(Shoot);

		if (shoot.shooting && shoot.cooldown == 0) {
			Utils::callExternalModule<void>(*shoot.handler, "attackDefault", *entity, this->_core, shoot.game);
			shoot.cooldown = shoot.startCooldown;
		} else if (shoot.cooldown)
			shoot.cooldown--;
		Utils::callExternalModule<void>(*shoot.handler, "update");
	}
}