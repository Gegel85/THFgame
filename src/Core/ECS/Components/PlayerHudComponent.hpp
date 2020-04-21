//
// Created by Gegel85 on 18/11/2019.
//

#ifndef THFGAME_PLAYERHUDCOMPONENT_HPP
#define THFGAME_PLAYERHUDCOMPONENT_HPP


#include "../../Rendering/Hud.hpp"
#include "BasicSerializeComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	//! @brief An Entity with a name.
	class PlayerHUDComponent : public BasicSerializeComponent {
	public:
		//! @brief The Screen to render the HUD on.
		Rendering::HUD &hud;

		PlayerHUDComponent(Rendering::HUD &hud);
		~PlayerHUDComponent() override;
	};
}


#endif //THFGAME_PLAYERHUDCOMPONENT_HPP
