//
// Created by anonymus-raccoon on 1/15/20.
//

#ifndef THFGAME_RECTANGLECOLLIDER_HPP
#define THFGAME_RECTANGLECOLLIDER_HPP

#include "CircleCollider.hpp"

namespace TouhouFanGame::ECS
{
	class RectangleCollider : public ICollider {
	public:
		FloatRect rect;
	};
}

#endif //THFGAME_RECTANGLECOLLIDER_HPP
