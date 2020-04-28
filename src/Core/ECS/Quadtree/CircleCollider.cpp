//
// Created by anonymus-raccoon on 1/15/20.
//

#include "CircleCollider.hpp"
#include "../Exceptions.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	CircleCollider::CircleCollider(float x, float y, float radius) :
		ICollider("Circle", {x - radius, y - radius}, Vector2f{radius, radius}),
		radius(radius)
	{
	}

	CircleCollider::CircleCollider(std::istream &stream) :
		ICollider("Circle", stream)
	{
		this->radius = this->_center.x - this->_offset.x;

		if (this->radius != this->_center.y - this->_offset.y)
			throw InvalidSerializedString("The center is not in the center of the circle.");
		if (this->radius < 0)
			throw InvalidSerializedString("The radius is invalid");
	}

	bool CircleCollider::collideWith(const class CircleCollider &col) const
	{
		return col.getCenter().distance(this->getCenter()) < this->radius + col.radius;
	}

	bool CircleCollider::collideWith(const class RectangleCollider &col) const
	{
//		float x = std::abs(this->center.x - col.rect.pt1.x);
//		float y = std::abs(this->center.y - col.rect.pt1.x);
//
//		return x <= this->size + col.rect.w && y <= this->size + col.rect.h;
		return col.collideWith(*this);
	}

	bool CircleCollider::collideWith(const ICollider &col) const
	{
		return col.collideWith(*this);
	}

	void CircleCollider::_serialize(std::ostream &stream) const
	{
	}

	void CircleCollider::draw(Rendering::Screen &screen) const
	{
		screen.draw(this->radius, this->_origin + this->_offset);
	}

	void CircleCollider::setRadius(float radius)
	{
		this->radius = radius;
		this->_offset = {
			this->_center.x - radius,
			this->_center.y - radius,
		};
	}
}