/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** ManaSystem.cpp
*/

#include "ManaSystem.hpp"
#include "../Components/ManaComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	ManaSystem::ManaSystem(TouhouFanGame::ECS::Core &parent) :
		System(parent, "Mana", {})
	{}

	void ManaSystem::updateEntity(TouhouFanGame::ECS::Entity &entity)
	{
		auto &mana = entity.getComponent("Health").to<Components::ManaComponent>();

		if (mana.mana > mana.maxMana)
			mana.mana = mana.maxMana;
	}
}