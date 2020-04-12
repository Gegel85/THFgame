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

	void ManaSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &mana = entity->getComponent(Mana);

		mana.mana = std::min(mana.mana, mana.maxMana);
	}
}