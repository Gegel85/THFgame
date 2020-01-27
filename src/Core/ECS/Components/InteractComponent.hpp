//
// Created by Gegel85 on 05/01/2020.
//

#ifndef THFGAME_INTERACTCOMPONENT_HPP
#define THFGAME_INTERACTCOMPONENT_HPP


#include "BasicSerializeComponent.hpp"
#include "../Entity.hpp"

namespace TouhouFanGame::ECS::Components
{
	//! @brief Entity you can interact with the interact key.
	class InteractComponent : public BasicSerializeComponent {
	public:
		std::weak_ptr<Entity> interactedWith;

		InteractComponent();
		~InteractComponent() override = default;
	};
}


#endif //THFGAME_INTERACTCOMPONENT_HPP
