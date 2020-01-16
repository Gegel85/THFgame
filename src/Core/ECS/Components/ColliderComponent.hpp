//
// Created by Gegel85 on 05/01/2020.
//

#ifndef THFGAME_COLLIDERCOMPONENT_HPP
#define THFGAME_COLLIDERCOMPONENT_HPP


#include "../System.hpp"
#include "BasicSerializeComponent.hpp"
#include "../Quadtree/ICollider.hpp"

namespace TouhouFanGame::ECS::Components
{
	class ColliderComponent : public Component {
	public:
		std::vector<std::unique_ptr<ICollider>> colliders;

		ColliderComponent(std::vector<ICollider *> &colliders);
		~ColliderComponent() override = default;
	};
}


#endif //THFGAME_COLLIDERCOMPONENT_HPP
