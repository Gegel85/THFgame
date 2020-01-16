//
// Created by anonymus-raccoon on 1/15/20.
//

#include <cmath>
#include "CircleCollider.hpp"
#include "../Components/ColliderComponent.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	bool CircleCollider::collideWith(CircleCollider &col)
	{
		return this->center.Distance(col.center) <= this->size + col.size;
	}

	bool CircleCollider::collideWith(Entity &entity)
	{
		auto &col = entity.getComponent("Collider").to<Components::ColliderComponent>();

		for (auto &collider : col.colliders) {
			if (collider->collideWith(*this))
				return true;
		}
		return false;
	}

	bool CircleCollider::collideWith(RectangleCollider &col)
	{
		int x = abs(this->center.x - col.rect.x);
		int y = abs(this->center.y - col.rect.y);

		return x <= this->size + col.rect.w && y <= this->size + col.rect.h;
	}
}