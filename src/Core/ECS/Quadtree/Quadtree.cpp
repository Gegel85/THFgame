//
// Created by anonymus-raccoon on 1/14/20.
//

#include <X11/Xlib.h>
#include "Quadtree.hpp"
#include "../Components/PositionComponent.hpp"

namespace TouhouFanGame::ECS
{
	Quadtree::Quadtree::Quadtree(unsigned entityCount, float x, float y, float w, float h)
		: _entityCount(entityCount), _quadCollider(x, y, w, h) {}

	void Quadtree::Quadtree::add(const std::shared_ptr<Entity> &entity)
	{
		if (this->_entities.size() <= this->_entityCount)
			this->_entities.push_back(entity);
		else if (this->_entityCount == 0) {
			for (auto &child : this->_children)
				child.add(entity);
		} else {
			this->split();
			this->add(entity);
		}
	}

	void Quadtree::Quadtree::split()
	{
		for (int i = 0; i < 4; i++) {
			Quadtree child(this->_entityCount,
						   this->_quadCollider.rect.x,
						   this->_quadCollider.rect.y,
						   this->_quadCollider.rect.w / 2,
						   this->_quadCollider.rect.h / 2);

			if (i % 2 == 1)
				child._quadCollider.rect.x += this->_quadCollider.rect.w / 2;
			if (i > 1)
				child._quadCollider.rect.y += this->_quadCollider.rect.h / 2;
			this->_children.push_back(child);
			for (auto &ent : this->_entities) {
				if (child._quadCollider.collideWith(*ent))
					child.add(ent);
			}
		}
		this->_entities.clear();
		this->_entityCount = 0;
	}

	void Quadtree::Quadtree::remove()
	{

	}
}