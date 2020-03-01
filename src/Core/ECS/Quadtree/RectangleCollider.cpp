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
	RectangleCollider::RectangleCollider(float x, float y, float w, float h, float angle)
			: ICollider(x, y, w, h), rect(0, 0, w, h, angle)
	{}

	bool RectangleCollider::collideWith(const CircleCollider &col) const
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

	int RectangleCollider::getCollisionLayer(const ICollider &collider) const
	{
		if (collider.collideWith(*this))
			return 0;
		return -1;
	}

	int RectangleCollider::getCollisionLayer(const std::vector<std::unique_ptr<ICollider>> &colliders) const
	{
		int layer = 0;

		for (auto &collider : colliders) {
			if (collider->collideWith(*this))
				return layer;
			layer++;
		}
		return -1;
	}

	float RectangleCollider::getSize() const
	{
		return 0;
	}

	void RectangleCollider::serialize(std::ostream &stream) const
	{
		stream << "1 " << this->offset << " " << this->size << " " << this->rect.getAngle();
	}

	void RectangleCollider::setOrigin(const Components::PositionComponent &pos)
	{
		this->rect = FloatRect(pos.position, pos.size, pos.angle);
	}
}
