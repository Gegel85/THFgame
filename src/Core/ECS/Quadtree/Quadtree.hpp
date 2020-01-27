//
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
		std::vector<Quadtree> _children{0};
		unsigned _entityCount = 0;
		std::vector<std::shared_ptr<Entity>> _entities{};
		RectangleCollider _quadCollider{0, 0, 0, 0, 0};

	public:
		Quadtree() = default;
		Quadtree(unsigned entityCount, float x, float y, float w, float h);
		void add(const std::shared_ptr<Entity>& entity);
		void update(const std::shared_ptr<Entity>& entity);
		std::vector<std::pair<std::shared_ptr<Entity>, unsigned>> checkCollisions(const ICollider &collider);
		void split();
        void reset();
		void remove(const std::shared_ptr<Entity> &entity);
	};

}

#endif //THFGAME_QUADTREE_HPP
