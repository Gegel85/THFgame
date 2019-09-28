//
// Created by Gegel85 on 28/09/2019.
//

#include <iostream>
#include "MovableSystem.hpp"
#include "../Components/PositionComponent.hpp"
#include "../Components/MovableComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	MovableSystem::MovableSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "Movable", {"Position"})
	{}

	void MovableSystem::updateEntity(TouhouFanGame::ECS::Entity &entity)
	{
		auto &pos = entity.getComponent("Position").to<Components::PositionComponent>();
		auto &mov = entity.getComponent("Movable").to<Components::MovableComponent>();

		pos.position.x += mov.speed * (((mov.dir & 0b0010U) != 0) - ((mov.dir & 0b1000U) != 0));
		pos.position.y += mov.speed * (((mov.dir & 0b0100U) != 0) - ((mov.dir & 0b0001U) != 0));
	}
}