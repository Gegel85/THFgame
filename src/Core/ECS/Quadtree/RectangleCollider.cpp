//
// Created by anonymus-raccoon on 1/15/20.
//

#include "RectangleCollider.hpp"
#include "../../DataType/Rect.hpp"

namespace TouhouFanGame::ECS
{
	RectangleCollider::RectangleCollider(float x, float y, float w, float h)
			: size(x, y, w, h)
	{}

	RectangleCollider::RectangleCollider(FloatRect rect)
		: rect(rect)
	{}

	bool RectangleCollider::collideWith(CircleCollider &col)
	{
		return col.collideWith((this);
	}

	bool RectangleCollider::collideWith(RectangleCollider &col)
	{
		if (this->rect.x > col.rect.x + col.rect.w && RectA.x)
			return false;
		return true;
		//> RectB.X1 && RectA.Y1 < RectB.Y2 && RectA.Y2 > RectB.Y1)
	}
}
