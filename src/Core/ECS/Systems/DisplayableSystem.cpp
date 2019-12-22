//
// Created by Gegel85 on 28/09/2019.
//

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

	void DisplayableSystem::updateEntity(TouhouFanGame::ECS::Entity &entity)
	{
		auto &pos = entity.getComponent("Position").to<Components::PositionComponent>();
		auto &disp = entity.getComponent("Displayable").to<Components::DisplayableComponent>();

		disp.renderEntity.setSize(pos.size);
		disp.renderEntity.setPosition(pos.position);
		disp.renderEntity.setAnimation(disp.animation, false);
		if (entity.hasComponent("Movable")) {
			unsigned dir = entity.getComponent("Movable").to<Components::MovableComponent>().dir;

			if (dir & TO_DIR(Input::LEFT) && dir & TO_DIR(Input::UP))
				disp.renderEntity.setDirection(Rendering::NORTH_WEST);
			else if (dir & TO_DIR(Input::RIGHT) && dir & TO_DIR(Input::UP))
				disp.renderEntity.setDirection(Rendering::NORTH_EAST);
			else if (dir & TO_DIR(Input::LEFT) && dir & TO_DIR(Input::DOWN))
				disp.renderEntity.setDirection(Rendering::SOUTH_WEST);
			else if (dir & TO_DIR(Input::RIGHT) && dir & TO_DIR(Input::DOWN))
				disp.renderEntity.setDirection(Rendering::SOUTH_EAST);
			else if (dir & TO_DIR(Input::LEFT))
				disp.renderEntity.setDirection(Rendering::WEST);
			else if (dir & TO_DIR(Input::DOWN))
				disp.renderEntity.setDirection(Rendering::SOUTH);
			else if (dir & TO_DIR(Input::RIGHT))
				disp.renderEntity.setDirection(Rendering::EAST);
			else
				disp.renderEntity.setDirection(Rendering::NORTH);
		}
		disp.renderEntity.update();
	}
}