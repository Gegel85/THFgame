//
// Created by anonymus-raccoon on 1/15/20.
//

#ifndef THFGAME_CIRCLECOLLIDER_HPP
#define THFGAME_CIRCLECOLLIDER_HPP

#include "RectangleCollider.hpp"
#include "../../DataType/Vector.hpp"
#include "ICollider.hpp"

namespace TouhouFanGame::ECS
{
	class CircleCollider : public ICollider {
	public:
		float size;
		Vector2f center;
		float angle;
	};
}

#endif //THFGAME_CIRCLECOLLIDER_HPP
