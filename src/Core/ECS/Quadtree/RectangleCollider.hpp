//
// Created by anonymus-raccoon on 1/15/20.
//

#ifndef THFGAME_RECTANGLECOLLIDER_HPP
#define THFGAME_RECTANGLECOLLIDER_HPP

#include "../../DataType/Rect.hpp"
#include "../Entity.hpp"
#include "ICollider.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	class RectangleCollider : public ICollider {
	public:

		bool collideWith(Entity &ent) override;
		bool collideWith(class CircleCollider &col) override;
		bool collideWith(RectangleCollider &col) override;
		float getSize() override;
		FloatRect rect;
		float angle;

		RectangleCollider(float x, float y, float w, float h, float angle);
		RectangleCollider(FloatRect rect);
	};
}

#endif //THFGAME_RECTANGLECOLLIDER_HPP
