//
// Created by anonymus-raccoon on 1/14/20.
//

#include "Quadtree.hpp"
#include "../Components/PositionComponent.hpp"

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
				if (child._quadCollider.collideWith(*ent))
					child.add(ent);
			}
		}
		this->_entities.clear();
		this->_entityCount = 0;
	}

	void Quadtree::remove()
	{

	}
}