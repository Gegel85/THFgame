//
// Created by Gegel85 on 28/09/2019.
//

#include "DisplayableSystem.hpp"
#include "../Components/PositionComponent.hpp"
#include "../Components/DisplayableComponent.hpp"

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
	}
}