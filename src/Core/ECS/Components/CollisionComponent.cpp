//
// Created by Gegel85 on 05/01/2020.
//

#include <algorithm>
#include "CollisionComponent.hpp"
#include "../Quadtree/ICollider.hpp"

namespace TouhouFanGame::ECS::Components
{
	CollisionComponent::CollisionComponent(Quadtree::ICollider *collider) :
			Component("Collision"), collider(collider)
	{
	}

	void CollisionComponent::serialize(std::ostream &stream) const
	{

	}
}