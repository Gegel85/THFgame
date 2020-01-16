//
// Created by anonymus-raccoon on 1/15/20.
//

#include "RectangleCollider.hpp"

namespace TouhouFanGame::ECS {
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
