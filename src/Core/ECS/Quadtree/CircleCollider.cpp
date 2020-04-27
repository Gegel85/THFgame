//
// Created by anonymus-raccoon on 1/15/20.
//

#include <cmath>
#include "CircleCollider.hpp"
#include "../Components/ColliderComponent.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	CircleCollider::CircleCollider(float x, float y, float radius) :
		ICollider("Circle", {x, y}, Vector2f{radius, radius}),
		radius(radius)
	{
	}

	CircleCollider::CircleCollider(std::istream &stream) :
		ICollider("Circle", stream)
	{
		stream >> this->radius;
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
		stream << this->radius;
	}

	void CircleCollider::draw(Rendering::Screen &screen) const
	{
		screen.draw(this->radius, this->_origin + this->_offset);
	}

	bool CircleCollider::operator>(const ICollider &collider) const
	{
		return !(collider > *this);
	}

	bool CircleCollider::operator>(const class CircleCollider &collider) const
	{
		return false;
	}

	bool CircleCollider::operator>(const class RectangleCollider &collider) const
	{
		return false;
	}
}