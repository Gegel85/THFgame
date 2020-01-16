//
// Created by anonymus-raccoon on 1/16/20.
//

#include "QuadEntity.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	QuadEntity::QuadEntity(std::shared_ptr<Entity> entity)
		: ptr(entity)
	{
		for (auto &cmp : entity->getComponent())
	}
}
