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
				shoot.shooting = true;
				break;
			case Input::INTERACT:
				for (auto &ent : col.collided)
					if (ent->hasComponent("Interact"))
						ent->getComponent("Interact").to<Components::InteractComponent>().interactedWith = entity;
				break;
			case Input::SPRINT:
				sprinting = true;
				break;
			default:
				break;
			}
		}

		if (dir & TO_DIR(Input::LEFT) && dir & TO_DIR(Input::RIGHT))
			dir &= ~TO_DIR(Input::LEFT) & ~TO_DIR(Input::RIGHT);
		if (dir & TO_DIR(Input::DOWN) && dir & TO_DIR(Input::UP))
			dir &= ~TO_DIR(Input::DOWN) & ~TO_DIR(Input::UP);

		if (dir) {
			mov.dir = dir;
			mov.speed = sprinting ? co.sprintSpeed : co.regularSpeed;
			dis.animation = static_cast<Rendering::Animation>(Rendering::WALK + sprinting);
		} else {
			mov.speed = 0;
			dis.animation = Rendering::IDLE;
		}
		if (shoot.shooting)
			dis.animation = Rendering::ATTACKING;
	}
}