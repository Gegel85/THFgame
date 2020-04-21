//
// Created by Gegel85 on 21/04/2020.
//

#include "BossHudSystem.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/BossHudComponent.hpp"
#include "../Components/NameComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	BossHUDSystem::BossHUDSystem(Core &core) :
		System(core, "BossHUD", {"Name", "Health"})
	{}

	void BossHUDSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &health = entity->getComponent(Health);
		auto &name = entity->getComponent(Name);
		auto &hud = entity->getComponent(BossHUD);

		hud.hud.setBossName(name.name);
		hud.hud.setBossLife(health.health * 100 / health.maxHealth);
	}
}
