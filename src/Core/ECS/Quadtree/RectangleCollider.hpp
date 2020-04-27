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
	protected:
		void _serialize(std::ostream &stream) const override;
		FloatRect _rect;

	public:
		bool collideWith(const struct CircleCollider &col) const override;
		bool collideWith(const class RectangleCollider &col) const override;
		bool collideWith(const ICollider &col) const override;

		FloatRect getRect() const;
		void draw(Rendering::Screen &screen) const override;

		RectangleCollider(std::istream &stream);
		RectangleCollider(float x, float y, float w, float h, float angle);
		explicit RectangleCollider(FloatRect rect);

		bool operator>(const ICollider &collider) const override;

		bool operator>(const struct CircleCollider &collider) const override;

		bool operator>(const class RectangleCollider &collider) const override;
	};
}

#endif //THFGAME_RECTANGLECOLLIDER_HPP
