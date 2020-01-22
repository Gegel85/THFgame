//
// Created by Gegel85 on 05/01/2020.
//

#include <iostream>
#include "CollisionSystem.hpp"
#include "../Core.hpp"
#include "../Components/CollisionComponent.hpp"
#include "../../Game.hpp"
#include "../Components/PositionComponent.hpp"
#include "../Components/ColliderComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	CollisionSystem::CollisionSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "Collision", {"Position"}),
		_quadtree(25,
			0,
			0,
			core.getGame().state.map.getSize().x,
			core.getGame().state.map.getSize().y
		)
	{}

	void CollisionSystem::update()
	{
		//this->_quadtree.reset(); TO IMPLEMENT
		for (auto &entity : _core.getEntityByComponent("Collider")) {
			auto &collider = entity->getComponent("Collider").to<Components::ColliderComponent &>();
			auto &pos = entity->getComponent("Position").to<Components::PositionComponent &>();

			std::for_each(collider.colliders.begin(), collider.colliders.end(), [&pos](std::unique_ptr<Quadtree::ICollider> &x) {
				x->setOrigin(pos);
			});
			this->_quadtree.add(entity);
		}

		for (auto &entity : _core.getEntityByComponent("Collision")) {
			auto &collider = entity->getComponent("Collision").to<Components::CollisionComponent &>();
			auto &pos = entity->getComponent("Position").to<Components::PositionComponent &>();

			if (!collider.collider)
				continue;
			collider.collider->setOrigin(pos);
			this->_quadtree.add(entity);
		}
	}

	void CollisionSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &collision = entity->getComponent("Collision").to<Components::CollisionComponent &>();

		collision.collided = this->_quadtree.checkCollisions(*collision.collider);
		if (!collision.collided.empty()) {
			std::cout << "Entity " << entity->getName() << " collided with: {" << std::endl;
			for (auto &col : collision.collided)
				std::cout << "\t" << col.first << ", " << col.second << std::endl;
			std::cout << "}" << std::endl;
		}
	}
}