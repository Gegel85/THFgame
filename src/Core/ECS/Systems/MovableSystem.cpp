//
// Created by Gegel85 on 28/09/2019.
//

#include <iostream>
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
		auto &pos = entity->getComponent("Position").to<Components::PositionComponent>();
		auto &mov = entity->getComponent("Movable").to<Components::MovableComponent>();

		pos.position.x += mov.speed * (((mov.dir & TO_DIR(Input::RIGHT)) != 0) - ((mov.dir & TO_DIR(Input::LEFT)) != 0));
		pos.position.y += mov.speed * (((mov.dir & TO_DIR(Input::DOWN)) != 0) - ((mov.dir & TO_DIR(Input::UP)) != 0));
	}
}