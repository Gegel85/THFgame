//
// Created by Gegel85 on 28/09/2019.
//

#include "ControllableSystem.hpp"
#include "../Components/ControllableComponent.hpp"
#include "../Components/MovableComponent.hpp"
#include "../Components/DisplayableComponent.hpp"
#include "../Core.hpp"
#include "../Components/CollisionComponent.hpp"
#include "../Components/InteractComponent.hpp"
#include "../Components/ShootComponent.hpp"

#define TO_DIR(val) (1U << val)

namespace TouhouFanGame::ECS::Systems
{
	ControllableSystem::ControllableSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "Controllable", {"Movable", "Position", "Displayable", "Collision"})
	{
	}

	void ControllableSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &co = entity->getComponent("Controllable").to<Components::ControllableComponent>();
		auto &mov = entity->getComponent("Movable").to<Components::MovableComponent>();
		auto &dis = entity->getComponent("Displayable").to<Components::DisplayableComponent>();
		auto &shoot = entity->getComponent("Shoot").to<Components::ShootComponent>();

		shoot.shooting = false;
		if (co.disabled) {
			mov.speed = 0;
			dis.animation = Rendering::IDLE;
			return;
		}

		auto &col = entity->getComponent("Collision").to<Components::CollisionComponent>();
		bool sprinting = false;
		bool moving = false;

		for (auto &action : co.input.getActions()) {
			switch (action) {
			case Input::UP:
			case Input::RIGHT:
			case Input::DOWN:
			case Input::LEFT:
				moving = true;
				break;
			case Input::ATTACK:
				shoot.shooting = true;
				break;
			case Input::INTERACT:
				for (auto &ent : col.collided)
					if (ent.first->hasComponent("Interact"))
						ent.first->getComponent("Interact").to<Components::InteractComponent>().interactedWith = entity;
				break;
			case Input::SPRINT:
				sprinting = true;
				break;
			default:
				break;
			}
		}

		if (moving) {
			mov.angleDir = co.input.getDirectionAngle();
			mov.speed = sprinting ? co.sprintSpeed : co.regularSpeed;
			dis.animation = sprinting ? Rendering::RUN : Rendering::WALK;
		} else {
			mov.speed = 0;
			dis.animation = Rendering::IDLE;
		}
		if (shoot.shooting)
			dis.animation = Rendering::ATTACKING;
	}
}