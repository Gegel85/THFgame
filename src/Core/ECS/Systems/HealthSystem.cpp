/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** HealthSystem.cpp
*/

#include "HealthSystem.hpp"
#include "../Components/HealthComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	HealthSystem::HealthSystem(TouhouFanGame::ECS::Core &parent) :
		System(parent, "Health", {})
	{}

	void HealthSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &health = entity->getComponent(Health);

		health.health = std::max(0.f, std::min(health.health, health.maxHealth));
		if (health.invulnerability)
			health.invulnerability--;
	}
}