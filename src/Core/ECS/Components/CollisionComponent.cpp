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
	CollisionComponent::CollisionComponent(Quadtree::ICollider *collider) :
			Component("Collision"), collider(collider)
	{}

	void CollisionComponent::serialize(std::ostream &stream) const
	{
		stream << *this->collider;
	}

	CollisionComponent::CollisionComponent(std::istream &stream)
		: Component("Collision")
	{
		stream >> this->collider;
	}
}