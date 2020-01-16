/
// Created by anonymus-raccoon on 1/14/20.
//

#ifndef THFGAME_QUADTREE_HPP
#define THFGAME_QUADTREE_HPP


#include <vector>
#include <memory>
#include "../Entity.hpp"
#include "../../DataType/Rect.hpp"
#include "RectangleCollider.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	//! @brief A quadtree to store entities in small groups.
	class Quadtree {
	private:
		std::vector<Quadtree> _children;
		unsigned _entityCount;
		std::vector<std::shared_ptr<Entity>> _entities;
		RectangleCollider _quadCollider;

	public:
		Quadtree(unsigned entityCount, float x, float y, float w, float h);
		void add(const std::shared_ptr<Entity>& entity);
		void split();
		void remove();
	};

}

#endif //THFGAME_QUADTREE_HPP
