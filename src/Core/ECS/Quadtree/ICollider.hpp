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
		virtual bool collideWith(Entity &entity) = 0;
		virtual bool collideWith(class CircleCollider &col) = 0;
		virtual bool collideWith(class RectangleCollider &col) = 0;
		virtual float getSize() = 0;
		virtual void serialize(std::ostream &stream) const = 0;
		static std::unique_ptr<ICollider> deserialize(std::istream &stream);
	};

	std::ostream &operator<<(std::ostream &stream, const ICollider &collider);
	std::istream &operator>>(std::istream &stream, std::unique_ptr<ICollider> &collider);
}

#endif //THFGAME_ICOLLIDER_HPP
