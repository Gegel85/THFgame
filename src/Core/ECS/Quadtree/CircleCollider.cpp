//
// Created by anonymus-raccoon on 1/15/20.
//

#include <cmath>
#include "CircleCollider.hpp"
#include "../Components/ColliderComponent.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	CircleCollider::CircleCollider(float x, float y, float size)
			: size(size), center(x, y)
	{}

	bool CircleCollider::collideWith(const CircleCollider &col) const
	{
		return this->center.distance(col.center) <= this->size + col.size;
	}

	bool CircleCollider::collideWith(const RectangleCollider &col) const
	{
//		float x = std::abs(this->center.x - col.rect.pt1.x);
//		float y = std::abs(this->center.y - col.rect.pt1.x);
//
//		return x <= this->size + col.rect.w && y <= this->size + col.rect.h;
		return true;
	}

	int CircleCollider::getCollisionLayer(const ICollider &collider) const
	{
		if (collider.collideWith(*this))
			return 0;
		return -1;
	}

	int CircleCollider::getCollisionLayer(const std::vector<std::unique_ptr<ICollider>> &colliders) const
	{
		int layer = 0;

		for (auto &collider : colliders) {
			if (collider->collideWith(*this))
				return layer;
			layer++;
		}
		return -1;
	}

	float CircleCollider::getSize() const
	{
		return 0;
	}

	void CircleCollider::serialize(std::ostream &stream) const
	{
        stream << "0 " << this->center << " " << this->size;
	}

	void CircleCollider::setOrigin(const Components::PositionComponent &pos)
	{
		this->center = pos.position + (pos.size / 2);
	}
}