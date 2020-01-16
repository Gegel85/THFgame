//
// Created by anonymus-raccoon on 1/14/20.
//

#ifndef THFGAME_QUADTREE_HPP
#define THFGAME_QUADTREE_HPP


#include <vector>
#include <memory>
#include "QuadEntity.hpp"
#include "../Entity.hpp"
#include "../../DataType/Rect.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	//! @brief A quadtree to store entities in small groups.
	class Quadtree {
	private:
		std::vector<Quadtree> _children;
		unsigned _entityCount;
		std::vector<std::shared_ptr<QuadEntity>> _entities;
		IntRect _rect;

	public:
		Quadtree(unsigned entityCount);
		void add(const std::shared_ptr<Entity>& entity);
		void remove();
	};

}

#endif //THFGAME_QUADTREE_HPP
