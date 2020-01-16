//
// Created by anonymus-raccoon on 1/15/20.
//

#include "RectangleCollider.hpp"
#include "../../DataType/Rect.hpp"
#include "../Components/ColliderComponent.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	RectangleCollider::RectangleCollider(float x, float y, float w, float h)
			: rect(x, y, w, h)
	{}

	RectangleCollider::RectangleCollider(FloatRect rect)
		: rect(rect)
	{}

	bool RectangleCollider::collideWith(Entity &entity)
	{
		auto &col = entity.getComponent("Collider").to<Components::ColliderComponent>();

		for (auto &collider : col.colliders) {
			if (collider->collideWith(*this))
				return true;
		}
		return false;
	}

	bool RectangleCollider::collideWith(CircleCollider &col)
	{
		return col.collideWith(*this);
	}

	bool RectangleCollider::collideWith(RectangleCollider &col)
	{
		return true;
	}
}
