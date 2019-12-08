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

	void HealthSystem::updateEntity(TouhouFanGame::ECS::Entity &entity)
	{
		auto &health = entity.getComponent("Health").to<Components::HealthComponent>();

		if (health.health > health.maxHealth)
			health.health = health.maxHealth;
	}
}