//
// Created by anonymus-raccoon on 1/15/20.
//

#ifndef THFGAME_CIRCLECOLLIDER_HPP
#define THFGAME_CIRCLECOLLIDER_HPP

#include "RectangleCollider.hpp"
#include "../../DataType/Vector.hpp"
#include "ICollider.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	class CircleCollider : public ICollider {
	private:
		void _serialize(std::ostream &stream) const override;

	public:
		float radius;

		CircleCollider(std::istream &stream);
		CircleCollider(float x, float y, float radius);

		bool collideWith(const class CircleCollider &col) const override;
		bool collideWith(const class RectangleCollider &col) const override;
		bool collideWith(const ICollider &col) const override;

		bool operator>(const ICollider &collider) const override;
		bool operator>(const class CircleCollider &collider) const override;
		bool operator>(const class RectangleCollider &collider) const override;

		void draw(Rendering::Screen &screen) const override;
	};
}

#endif //THFGAME_CIRCLECOLLIDER_HPP
