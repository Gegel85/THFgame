//
// Created by Gegel85 on 28/09/2019.
//

#include <iostream>
#include <cmath>
#include "MovableSystem.hpp"
#include "../Components/PositionComponent.hpp"
#include "../Components/MovableComponent.hpp"
#include "../../Input/Input.hpp"

namespace TouhouFanGame::ECS::Systems
{
	MovableSystem::MovableSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "Movable", {"Position"})
	{}

	void MovableSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &pos = entity->getComponent(Position);
		auto &mov = entity->getComponent(Movable);

		pos.position.x += mov.speed * cos(mov.angleDir);
		pos.position.y += mov.speed * sin(mov.angleDir);
	}
}