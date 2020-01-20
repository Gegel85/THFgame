//
// Created by Gegel85 on 28/09/2019.
//

#include <iostream>
#include "DisplayableSystem.hpp"
#include "../Components/PositionComponent.hpp"
#include "../Components/DisplayableComponent.hpp"
#include "../Components/MovableComponent.hpp"
#include "../../Input/Input.hpp"

namespace TouhouFanGame::ECS::Systems
{
	DisplayableSystem::DisplayableSystem(TouhouFanGame::ECS::Core &_parent) :
		System(_parent, "Displayable", {"Position"})
	{
	}

	void DisplayableSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &pos = entity->getComponent("Position").to<Components::PositionComponent>();
		auto &disp = entity->getComponent("Displayable").to<Components::DisplayableComponent>();

		disp.renderEntity.setSize(pos.size);
		disp.renderEntity.setPosition(pos.position);
		disp.renderEntity.setAnimation(disp.animation, false);
		disp.renderEntity.setDirection(disp.dir);
		disp.renderEntity.setSpriteAngle(disp.spriteAngle);
		disp.renderEntity.update();
	}
}