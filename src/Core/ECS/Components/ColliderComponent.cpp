//
// Created by Gegel85 on 05/01/2020.
//

#include "ColliderComponent.hpp"
#include <algorithm>

namespace TouhouFanGame::ECS::Components
{
	ColliderComponent::ColliderComponent(std::vector<Quadtree::ICollider *> &colliders) :
		Component("Collider")
	{
		for (auto col : colliders)
			this->colliders.emplace_back(col);
		std::sort(this->colliders.begin(), this->colliders.end(), [](Quadtree::ICollider &a, Quadtree::ICollider &b) {
			return a.getSize() > b.getSize();
		});
	}
}
