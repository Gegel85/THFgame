//
// Created by Gegel85 on 05/01/2020.
//

#include <iostream>
#include "CollisionSystem.hpp"
#include "../Core.hpp"
#include "../Components/CollisionComponent.hpp"
#include "../../Game.hpp"
#include "../Components/PositionComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	CollisionSystem::CollisionSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "Collision", {"Position"}),
		quadtree(
			new Quadtree::Quadtree(
				25,
				0,
				0,
				core.getGame().state.map.getSize().x,
				core.getGame().state.map.getSize().y
			)
		)
	{}

	void CollisionSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &collision = entity->getComponent("Collision").to<Components::CollisionComponent &>();
		auto &pos = entity->getComponent("Position").to<Components::PositionComponent &>();

		collision.collider->setOrigin(pos);
		quadtree->update(entity);
		collision.collided = this->quadtree->checkCollisions(*collision.collider);
		if (!collision.collided.empty()) {
			std::cout << "Entity " << entity->getName() << " collided with: {" << std::endl;
			for (auto &col : collision.collided)
				std::cout << "\t" << col.first << ", " << col.second << std::endl;
			std::cout << "}" << std::endl;
		}
	}
}