//
// Created by anonymus-raccoon on 1/15/20.
//

#ifndef THFGAME_RECTANGLECOLLIDER_HPP
#define THFGAME_RECTANGLECOLLIDER_HPP

#include "CircleCollider.hpp"
#include "../../DataType/Rect.hpp"

namespace TouhouFanGame::ECS
{
	class RectangleCollider : public ICollider {
	public:
		bool collideWith(CircleCollider &col) override;
		bool collideWith(RectangleCollider &col) override;
		float getSize() override;
		bool collideWith(Entity &entity) override;
		FloatRect rect;

		RectangleCollider(float x, float y, float w, float h);
		RectangleCollider(FloatRect rect);
	};
}

#endif //THFGAME_RECTANGLECOLLIDER_HPP
