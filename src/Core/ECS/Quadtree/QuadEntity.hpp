//
// Created by anonymus-raccoon on 1/16/20.
//

#ifndef THFGAME_QUADENTITY_HPP
#define THFGAME_QUADENTITY_HPP


#include <vector>
#include <memory>
#include "../Entity.hpp"
#include "ICollider.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	class QuadEntity {
	public:
		std::shared_ptr<Entity> ptr;
		std::vector<ICollider> colliders;
		QuadEntity(std::shared_ptr<Entity> entity);
	};
}


#endif //THFGAME_QUADENTITY_HPP
