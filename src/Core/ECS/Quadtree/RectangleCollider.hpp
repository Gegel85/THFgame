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
		bool collideWith(const class CircleCollider &col) const override;
		bool collideWith(const class RectangleCollider &col) const override;
		bool collideWith(const ICollider &col) const override;

		FloatRect getRect() const;
		void draw(Rendering::Screen &screen) const override;
		Vector2<unsigned> getSize() const;
		void setSize(Vector2<unsigned> size);

		RectangleCollider(std::istream &stream);
		RectangleCollider(float x, float y, float w, float h, float angle);
	};
}

#endif //THFGAME_RECTANGLECOLLIDER_HPP
