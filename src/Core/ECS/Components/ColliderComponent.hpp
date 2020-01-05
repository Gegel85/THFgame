//
// Created by Gegel85 on 05/01/2020.
//

#ifndef THFGAME_COLLIDERCOMPONENT_HPP
#define THFGAME_COLLIDERCOMPONENT_HPP


#include "../System.hpp"
#include "BasicSerializeComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	class ColliderComponent : public BasicSerializeComponent {
	public:
		ColliderComponent();
		~ColliderComponent() override = default;
	};
}


#endif //THFGAME_COLLIDERCOMPONENT_HPP
