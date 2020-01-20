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
		bool collideWith(const class CircleCollider &col) const override;
		bool collideWith(const RectangleCollider &col) const override;
		int getCollisionLayer(const std::shared_ptr<Entity> &entity) const override;
		float getSize() const override;
		void serialize(std::ostream &stream) const override;
		FloatRect rect;

		RectangleCollider(float x, float y, float w, float h, float angle);
		explicit RectangleCollider(FloatRect rect);
	};
}

#endif //THFGAME_RECTANGLECOLLIDER_HPP
