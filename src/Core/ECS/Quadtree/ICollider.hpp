//
// Created by anonymus-raccoon on 1/16/20.
//

#ifndef THFGAME_ICOLLIDER_HPP
#define THFGAME_ICOLLIDER_HPP


#include "../Entity.hpp"

namespace TouhouFanGame::ECS {

	class ICollider {
	public:
		virtual bool collideWith(class CircleCollider &col) = 0;
		virtual bool collideWith(class RectangleCollider &col) = 0;
		virtual bool collideWith(Entity &entity) = 0;
		virtual float getSize() = 0;
	};
}

#endif //THFGAME_ICOLLIDER_HPP
