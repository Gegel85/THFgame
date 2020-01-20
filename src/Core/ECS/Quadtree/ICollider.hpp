//
// Created by anonymus-raccoon on 1/16/20.
//

#ifndef THFGAME_ICOLLIDER_HPP
#define THFGAME_ICOLLIDER_HPP


#include "../Entity.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	class ICollider {
	public:
		virtual bool collideWithEntity(const std::shared_ptr<Entity> &entity) const;
		virtual bool collideWith(const class CircleCollider &col) const = 0;
		virtual bool collideWith(const class RectangleCollider &col) const = 0;
		virtual int getCollisionLayer(const std::shared_ptr<Entity> &entity) const = 0;
		virtual float getSize() const = 0;
		virtual void serialize(std::ostream &stream) const = 0;
		static std::unique_ptr<ICollider> deserialize(std::istream &stream);
	};
}

std::ostream &operator<<(std::ostream &stream, const TouhouFanGame::ECS::Quadtree::ICollider &collider);
std::istream &operator>>(std::istream &stream, std::unique_ptr<TouhouFanGame::ECS::Quadtree::ICollider> &collider);

#endif //THFGAME_ICOLLIDER_HPP
