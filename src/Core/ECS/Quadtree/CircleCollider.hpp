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
	public:
		bool collideWith(Entity &entity) override;
		bool collideWith(CircleCollider &col) override;
		bool collideWith(RectangleCollider &col) override;
		void serialize(std::ostream &stream) const override;
		float getSize() override;
		float size;
		Vector2f center;

		CircleCollider(float x, float y, float size);
	};
}

#endif //THFGAME_CIRCLECOLLIDER_HPP
