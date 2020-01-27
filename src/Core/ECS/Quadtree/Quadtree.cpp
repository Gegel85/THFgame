//
// Created by anonymus-raccoon on 1/14/20.
//

#include <iostream>
#include "Quadtree.hpp"
#include "../Components/PositionComponent.hpp"
#include "../Components/ColliderComponent.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	Quadtree::Quadtree(unsigned entityCount, float x, float y, float w, float h)
		: _entityCount(entityCount), _quadCollider(x, y, w, h, 0) {}

	void Quadtree::add(const std::shared_ptr<Entity> &entity)
	{
		if (this->_entities.size() <= this->_entityCount)
			this->_entities.push_back(entity);
		else if (this->_entityCount == 0) {
			for (auto &child : this->_children)
				if (this->_quadCollider.collideWithEntity(entity))
					child.add(entity);
		} else {
			this->split();
			this->add(entity);
		}
	}

	void Quadtree::split()
	{
		for (int i = 0; i < 4; i++) {
			float width = this->_quadCollider.rect.pt2.distance(this->_quadCollider.rect.pt1) / 2;
			float height = this->_quadCollider.rect.pt1.distance(this->_quadCollider.rect.pt3) / 2;
			Quadtree child(this->_entityCount,
						   this->_quadCollider.rect.pt1.x,
						   this->_quadCollider.rect.pt1.y,
						   width,
						   height
						   );

			if (i % 2 == 1) {
				child._quadCollider.rect.pt1.x += width;
				child._quadCollider.rect.pt3.x += width;
			} if (i > 1) {
				child._quadCollider.rect.pt1.y += height;
				child._quadCollider.rect.pt2.y += height;
			}
			this->_children.push_back(child);
			for (auto &ent : this->_entities) {
				if (child._quadCollider.collideWithEntity(ent))
					child.add(ent);
			}
		}
		this->_entities.clear();
		this->_entityCount = 0;
	}

	void Quadtree::remove(const std::shared_ptr<Entity> &entity)
	{
		if (this->_entityCount == 0) {
			for (auto &child : this->_children)
				child.remove(entity);
			return;
		}
		this->_entities.erase(std::remove(this->_entities.begin(), this->_entities.end(), entity), this->_entities.end());
	}

	void Quadtree::update(const std::shared_ptr<Entity> &entity)
	{
		this->remove(entity);
		this->add(entity);
	}

	std::vector<std::pair<std::shared_ptr<Entity>, unsigned>> Quadtree::checkCollisions(const ICollider &collider)
	{
		std::vector<std::pair<std::shared_ptr<Entity>, unsigned int>> ret;
		int collisionLayer;

		if (this->_entityCount == 0) {
			for (auto &child : this->_children) {
				const auto &cols = child.checkCollisions(collider);
				ret.insert(ret.end(), cols.begin(), cols.end());
			}
		} else {
			for (auto &obj : this->_entities) {
				if (!obj->hasComponent("Collider"))
					continue;
				auto &col = obj->getComponent("Collider").to<Components::ColliderComponent>();
				collisionLayer = collider.getCollisionLayer(col.colliders);
				if (collisionLayer >= 0)
					ret.emplace_back(obj, collisionLayer);
			}
		}
		return ret;
	}

    void Quadtree::reset()
    {
//		std::cout << "Quadtree content: " << std::endl;
//        for (auto &ent : this->_entities)
//			std::cout << "\t" << ent->getName() << " " << ent->hasComponent("Collision") << " " << ent->getComponent("Position") << std::endl;
//		std::cout << std::endl;

		if (this->_entityCount == 0)
			for (auto &child : this->_children)
				child.reset();
		this->_entities.clear();
    }
}