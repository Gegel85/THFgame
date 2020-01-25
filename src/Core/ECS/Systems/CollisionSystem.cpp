//
// Created by Gegel85 on 05/01/2020.
//

#include "CollisionSystem.hpp"
#include "../Core.hpp"
#include "../Components/PositionComponent.hpp"
#include "../Components/CollisionComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	CollisionSystem::CollisionSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "Collision", {"Position"})
	{
	}

	void CollisionSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &pos = entity->getComponent("Position").to<Components::PositionComponent &>();
		auto &collision = entity->getComponent("Collision").to<Components::CollisionComponent &>();

		collision.collided.clear();
		for (auto &e : this->_core.getEntityByComponent("Collider")) {
			auto ent = e.lock();
			auto &ePos = ent->getComponent("Position").to<Components::PositionComponent &>();

			if (
				pos.position.x < ePos.position.x + ePos.size.x &&
				pos.position.y < ePos.position.y + ePos.size.y &&
				pos.position.x + pos.size.x > ePos.position.x &&
				pos.position.y + pos.size.y > ePos.position.y
			)
				collision.collided.push_back(ent);
		}
	}
}