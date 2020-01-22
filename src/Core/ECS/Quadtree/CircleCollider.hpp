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
		float size;
		Vector2f center;
	public:
		bool collideWith(const CircleCollider &col) const override;
		bool collideWith(const RectangleCollider &col) const override;
		int getCollisionLayer(const ICollider &colliders) const override;
		int getCollisionLayer(const std::vector<std::unique_ptr<ICollider>> &colliders) const override;
		void serialize(std::ostream &stream) const override;
		float getSize() const override;
		void setOrigin(const Components::PositionComponent &pos) override;

		CircleCollider(float x, float y, float size);
	};
}

#endif //THFGAME_CIRCLECOLLIDER_HPP
