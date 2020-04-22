//
// Created by Gegel85 on 05/01/2020.
//

#include "ColliderComponent.hpp"
#include "../Exceptions.hpp"
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
		stream << this->colliders.size();
		for (auto &elem : this->colliders)
			stream << " " << *elem;
	}

	ColliderComponent::ColliderComponent(std::istream &istream)
		: Component("Collider")
	{
		unsigned len = 0;

		istream >> len;
		if (istream.fail())
			throw InvalidSerializedString("Invalid ColliderComponent");
		this->colliders.resize(len);
		while (len--)
			istream >> this->colliders[len];
	}
}
