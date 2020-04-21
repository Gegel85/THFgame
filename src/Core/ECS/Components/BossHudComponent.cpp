//
// Created by Gegel85 on 21/04/2020.
//

#include "BossHudComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	BossHUDComponent::BossHUDComponent(TouhouFanGame::Rendering::HUD &hud) :
		BasicSerializeComponent("BossHUD"),
		hud(hud)
	{
	}

	BossHUDComponent::~BossHUDComponent()
	{
		hud.setDispBossHUD(false);
	}
}