//
// Created by Gegel85 on 05/01/2020.
//

#include "ColliderComponent.hpp"
#include <algorithm>

namespace TouhouFanGame::ECS::Components
{
	ColliderComponent::ColliderComponent(const std::vector<Quadtree::ICollider *> &colliders) :
		Component("Collider")
	{
		for (auto col : colliders)
			this->colliders.emplace_back(col);
		std::sort(this->colliders.begin(), this->colliders.end(), [](const std::unique_ptr<Quadtree::ICollider> &a, const std::unique_ptr<Quadtree::ICollider> &b) {
			return a->getSize() > b->getSize();
		});
	}

	void ColliderComponent::serialize(std::ostream &stream) const
	{

	}

	ColliderComponent::ColliderComponent(std::istream &istream)
		: Component("Collider")
	{

	}
}
