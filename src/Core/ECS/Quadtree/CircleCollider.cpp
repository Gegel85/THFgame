//
// Created by anonymus-raccoon on 1/15/20.
//

#include <cmath>
#include "CircleCollider.hpp"
#include "../Components/ColliderComponent.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	CircleCollider::CircleCollider(float x, float y, float size)
			: ICollider(x, y, size, size), _center(0, 0)
	{}

	bool CircleCollider::collideWith(const CircleCollider &col) const
	{
		return this->_center.distance(col._center) <= this->size.x + col.size.x;
	}

	bool CircleCollider::collideWith(const RectangleCollider &col) const
	{
//		float x = std::abs(this->_center.x - col.rect.pt1.x);
//		float y = std::abs(this->_center.y - col.rect.pt1.x);
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
		return this->size.x;
	}

	void CircleCollider::serialize(std::ostream &stream) const
	{
		stream << "0 " << this->offset << " " << this->getSize();
	}

	void CircleCollider::setOrigin(const Components::PositionComponent &pos)
	{
		this->_center = pos.position + (this->size / 2) + this->offset;
	}
}