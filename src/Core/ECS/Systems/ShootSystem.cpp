//
// Created by Gegel85 on 12/01/2020.
//

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
		auto &shoot = entity->getComponent("Shoot").to<Components::ShootComponent>();

		if (shoot.shooting)
			Utils::callExternalModule<void>(*shoot.handler, "attackDefault", *entity, this->_core, shoot.resources, shoot.map);
		Utils::callExternalModule<void>(*shoot.handler, "update");
	}
}