//
// Created by Gegel85 on 18/11/2019.
//

#include "PlayerHudComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	PlayerHUDComponent::PlayerHUDComponent(TouhouFanGame::Rendering::HUD &hud) :
		BasicSerializeComponent("PlayerHUD"),
		hud(hud)
	{
	}

	PlayerHUDComponent::~PlayerHUDComponent()
	{
		hud.setDispPlayerHUD(false);
	}
}