//
// Created by Gegel85 on 05/01/2020.
//

#include <iostream>
#include "CollisionSystem.hpp"
#include "../Core.hpp"
#include "../Components/DisplayableComponent.hpp"
#include "../Components/CollisionComponent.hpp"
#include "../../Resources/Game.hpp"
#include "../Components/ColliderComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	CollisionSystem::CollisionSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "Collision", {"Position"})//,
		/*_quadtree(25,
			0,
			0,
			core.getGame().state.map.getSize().x,
			core.getGame().state.map.getSize().y
		)*/
	{}

	void CollisionSystem::update()
	{
		//this->_quadtree.reset();
		for (auto &ent : this->_core.getEntityByComponent("Collider")) {
			auto entity = ent.lock();
			auto &collider = entity->getComponent(Collider);
			auto &pos = entity->getComponent(Position);

			std::for_each(collider.colliders.begin(), collider.colliders.end(), [&pos](std::unique_ptr<Quadtree::ICollider> &x) {
				x->setOrigin(pos.position);
			});
		//	this->_quadtree.add(entity);
		}

		/*for (auto &ent : this->_core.getEntityByComponent("Collision")) {
			auto entity = ent.lock();
			auto &collider = entity->getComponent(Collision);
			auto &pos = entity->getComponent(Position);

			if (!collider.collider)
				continue;
			collider.collider->setOrigin(pos);
			this->_quadtree.add(entity);
		}*/
	}

	void CollisionSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &collision = entity->getComponent(Collision);

		collision.collided.clear();
		collision.collider->setOrigin(entity->getComponent(Position).position);

		for (auto &ent : this->_core.getEntityByComponent("Collider")) {
			auto ptr = ent.lock();
			auto &collider = ptr->getComponent(Collider);
			auto layer = collision.collider->getCollisionLayer(collider.colliders);

			if (layer >= 0)
				collision.collided.emplace_back(ptr, layer);
		}
		/*collision.collided = this->_quadtree.checkCollisions(*collision.collider);
		if (!collision.collided.empty()) {
			std::cout << "Entity " << entity->getName() << " collided with: {" << std::endl;
			for (auto &col : collision.collided)
				std::cout << "\t" << col.first << ", " << col.second << std::endl;
			std::cout << "}" << std::endl;
		}*/
	}
}