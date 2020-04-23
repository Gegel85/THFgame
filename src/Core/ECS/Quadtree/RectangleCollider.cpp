//
// Created by anonymus-raccoon on 1/15/20.
//

#include "RectangleCollider.hpp"
#include "CircleCollider.hpp"
#include "../../DataType/Rect.hpp"
#include "../Components/ColliderComponent.hpp"
#include "../../Utils/Utils.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	RectangleCollider::RectangleCollider(std::istream &stream) :
		ICollider("Rectangle", stream),
		rect(this->_offset, (this->_center - this->_offset) * 2, this->_angle)
	{
	}

	RectangleCollider::RectangleCollider(float x, float y, float w, float h, float angle) :
		ICollider("Rectangle", Vector2f{x, y}, Vector2u(w, h), angle),
		rect(x, y, w, h, angle)
	{
	}

	bool RectangleCollider::collideWith(const class CircleCollider &col) const
	{
		throw NotImplementedException("Collision between circles and Rectangles are not implemented");
	}

	bool RectangleCollider::collideWith(const ICollider &col) const
	{
		return col.collideWith(*this);
	}

	bool RectangleCollider::collideWith(const RectangleCollider &col) const
	{
		return this->rect.pt1.x < col.rect.pt2.x &&
		       this->rect.pt1.y < col.rect.pt3.y &&
		       this->rect.pt2.x > col.rect.pt1.x &&
		       this->rect.pt3.y > col.rect.pt2.y;
		//		std::vector<Vector2f> axes;
//
//		axes.push_back(Vector2f(this->rect.pt1.x, this->rect.pt2.x - this->rect.pt1.x).normalize());
//		axes.push_back(Vector2f(this->rect.pt1.y, this->rect.pt2.y - this->rect.pt1.y).normalize());
//		axes.push_back(Vector2f(col.rect.pt1.x, col.rect.pt2.x - col.rect.pt1.x).normalize());
//		axes.push_back(Vector2f(col.rect.pt1.y, col.rect.pt2.y - col.rect.pt1.y).normalize());
//		for (auto &axe : axes) {
//			float proj1rect1 = this->rect.pt1 * axe;
//			float proj2rect1 = this->rect.pt2 * axe;
//			float proj3rect1 = this->rect.pt3 * axe;
//			float proj4rect1 = this->rect.pt4 * axe;
//			float proj1rect2 = col.rect.pt1 * axe;
//			float proj2rect2 = col.rect.pt2 * axe;
//			float proj3rect2 = col.rect.pt3 * axe;
//			float proj4rect2 = col.rect.pt4 * axe;
//			float min1 = axe * Utils::min(proj1rect1, proj2rect1, proj3rect1, proj4rect1) * axe;
//			float max1 = axe * Utils::max(proj1rect1, proj2rect1, proj3rect1, proj4rect1) * axe;
//			float min2 = axe * Utils::max(proj1rect2, proj2rect2, proj3rect2, proj4rect2) * axe;
//			float max2 = axe * Utils::max(proj1rect2, proj2rect2, proj3rect2, proj4rect2) * axe;
//
//			if (min1 < max2 || min2 < max1)
//				return false;
//		}
//		return true;
	}

	void RectangleCollider::_serialize(std::ostream &) const
	{
	}

	void RectangleCollider::draw(Rendering::Screen &screen) const
	{
		auto pos = this->_offset + this->_origin;
		auto size = (this->_center - this->_offset) * 2;

		screen.fillColor({0xFF, 0x00, 0x00, 0x20});
		screen.draw({
			static_cast<int>(pos.x),
			static_cast<int>(pos.y),
			static_cast<int>(size.x),
			static_cast<int>(size.y)
		});
	}

	bool RectangleCollider::operator>(const ICollider &collider) const
	{
		return !(collider > *this);
	}

	bool RectangleCollider::operator>(const class CircleCollider &collider) const
	{
		return false;
	}

	bool RectangleCollider::operator>(const class RectangleCollider &collider) const
	{
		return false;
	}
}
