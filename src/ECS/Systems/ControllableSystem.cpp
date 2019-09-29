//
// Created by Gegel85 on 28/09/2019.
//

#include "ControllableSystem.hpp"
#include "../Components/ControllableComponent.hpp"
#include "../Components/MovableComponent.hpp"
#include "../Components/DisplayableComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	ControllableSystem::ControllableSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "Controllable", {"Movable", "Position", "Displayable"})
	{
	}

	void ControllableSystem::updateEntity(TouhouFanGame::ECS::Entity &entity)
	{
		auto &co = entity.getComponent("Controllable").to<Components::ControllableComponent>();

		if (co.disabled)
			return;

		auto &mov = entity.getComponent("Movable").to<Components::MovableComponent>();
		auto &dis = entity.getComponent("Displayable").to<Components::DisplayableComponent>();
		unsigned char dir = 0;
		bool sprinting = false;

		for (auto &action : co.input.getActions()) {
			switch (action) {
			case Input::UP:
			case Input::RIGHT:
			case Input::DOWN:
			case Input::LEFT:
				dir |= 1U << action;
				break;
			case Input::ATTACK:
				break;
			case Input::INTERACT:
				break;
			case Input::SPRINT:
				sprinting = true;
				break;
			default:
				break;
			}
		}

		if (dir & 0b1000U && dir & 0b0010U)
			dir &= 0b0101U;
		if (dir & 0b0100U && dir & 0b0001U)
			dir &= 0b1010U;

		if (dir) {
			mov.dir = dir;
			mov.speed = sprinting ? co.sprintSpeed : co.regularSpeed;
			dis.animation = static_cast<Rendering::Animation>(Rendering::WALK + sprinting);
		} else {
			mov.speed = 0;
			dis.animation = Rendering::IDLE;
		}
	}
}