//
// Created by Gegel85 on 05/01/2020.
//

#ifndef THFGAME_COLLISIONCOMPONENT_HPP
#define THFGAME_COLLISIONCOMPONENT_HPP


#include <memory>
#include "BasicSerializeComponent.hpp"
#include "../Entity.hpp"

namespace TouhouFanGame::ECS::Components
{
	class CollisionComponent : public BasicSerializeComponent {
	public:
		std::vector<std::shared_ptr<ECS::Entity>> _collided;

		CollisionComponent();
		~CollisionComponent() override = default;
	};
}


#endif //THFGAME_COLLISIONCOMPONENT_HPP
