/*
** EPITECH PROJECT, 2020
** THFgame
** File description:
** OobDieSystem.cpp
*/

#include <iostream>
#include "OobDieSystem.hpp"
#include "../Components/PositionComponent.hpp"
#include "../Components/OobDieComponent.hpp"
#include "../../Utils/Utils.hpp"

namespace TouhouFanGame::ECS::Systems
{
	OOBDieSystem::OOBDieSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "OOBDie", {"Position"})
	{}

	void OOBDieSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &pos = entity->getComponent(Position);
		auto size = entity->getComponent(OOBDie).map.getPixelSize();

		if (
			pos.position.x < -static_cast<float>(pos.size.x) ||
			pos.position.y < -static_cast<float>(pos.size.y) ||
			pos.position.x > size.x ||
			pos.position.y > size.y
		)
			entity->destroy();
	}
}