//
// Created by Gegel85 on 05/01/2020.
//

#include <algorithm>
#include "CollisionComponent.hpp"
#include "../Quadtree/ICollider.hpp"

namespace TouhouFanGame::ECS::Components
{
	CollisionComponent::CollisionComponent(ICollider *colliders) :
			Component("Collision"), colliders(colliders)
	{
	}
}