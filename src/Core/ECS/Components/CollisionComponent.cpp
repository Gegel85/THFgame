//
// Created by Gegel85 on 05/01/2020.
//

#include <algorithm>
#include <iostream>
#include "CollisionComponent.hpp"
#include "../Quadtree/ICollider.hpp"
#include "../Quadtree/RectangleCollider.hpp"
#include "../Quadtree/CircleCollider.hpp"
#include "../Exceptions.hpp"

namespace TouhouFanGame::ECS::Components
{
	CollisionComponent::CollisionComponent(const std::vector<Quadtree::ICollider *> &colliders) :
		Component("Collision")
	{
		for (auto col : colliders)
			this->colliders.emplace_back(col);
		std::sort(this->colliders.begin(), this->colliders.end());
	}

	CollisionComponent::CollisionComponent(std::istream &stream) :
		Component("Collision")
	{
		unsigned len = 0;

		stream >> len;
		if (stream.fail())
			throw InvalidSerializedString("Invalid ColliderComponent");
		this->colliders.resize(len);
		while (len--)
			stream >> this->colliders[len];
	}

	void CollisionComponent::serialize(std::ostream &stream) const
	{
		stream << this->colliders.size();
		for (auto &elem : this->colliders)
			stream << " " << *elem;
	}
}