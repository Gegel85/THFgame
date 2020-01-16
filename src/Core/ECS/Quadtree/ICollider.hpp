//
// Created by anonymus-raccoon on 1/16/20.
//

#ifndef THFGAME_ICOLLIDER_HPP
#define THFGAME_ICOLLIDER_HPP

#include "CircleCollider.hpp"

namespace TouhouFanGame::ECS {

	class ICollider {
	public:
		virtual bool collideWith(CircleCollider &col) = 0;
		virtual bool collideWith(RectangleCollider &col) = 0;
	};
}

#endif //THFGAME_ICOLLIDER_HPP
