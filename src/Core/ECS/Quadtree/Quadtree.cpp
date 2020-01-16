//
// Created by anonymus-raccoon on 1/14/20.
//

#include <X11/Xlib.h>
#include "Quadtree.hpp"
#include "../Components/PositionComponent.hpp"

namespace TouhouFanGame::ECS {
	Quadtree::Quadtree::Quadtree(unsigned entityCount)
			: _entityCount(entityCount) {}

	void Quadtree::Quadtree::add(const std::shared_ptr<Entity> &entity) {
		if (this->_entityCount < this->_entities.size()) {
			this->_children.resize(4, Quadtree(this->_entityCount));
			for (auto &ent : this->_entities) {
				if (entityIsInRect(ent, this->_rect))
			}
			this->_entities.clear();
		} else {
			this->_entities.push_back(QuadEntity(entity, ));
		}
	}

	void Quadtree::Quadtree::remove() {

	}
}