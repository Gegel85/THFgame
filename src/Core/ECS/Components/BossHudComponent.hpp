//
// Created by Gegel85 on 21/04/2020.
//

#ifndef THFGAME_BOSSHUDCOMPONENT_HPP
#define THFGAME_BOSSHUDCOMPONENT_HPP


#include "../../Rendering/Hud.hpp"
#include "BasicSerializeComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	//! @brief An Entity with a name.
	class BossHUDComponent : public BasicSerializeComponent {
	public:
		//! @brief The Screen to render the HUD on.
		Rendering::HUD &hud;

		BossHUDComponent(Rendering::HUD &hud);
		~BossHUDComponent() override;
	};
}


#endif //THFGAME_BOSSHUDCOMPONENT_HPP
