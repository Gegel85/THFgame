//
// Created by Gegel85 on 28/09/2019.
//

#include <iostream>
#include "SystemFactory.hpp"
#include "../Systems/DisplayableSystem.hpp"
#include "../Systems/ControllableSystem.hpp"
#include "../Systems/MovableSystem.hpp"
#include "../Systems/UselessSystem.hpp"
#include "../Systems/BlockedByTerrainSystem.hpp"
#include "../Systems/HealthSystem.hpp"
#include "../Systems/ManaSystem.hpp"
#include "../Systems/PlayerHudSystem.hpp"
#include "../Systems/CollisionSystem.hpp"
#include "../Systems/DialogSystem.hpp"
#include "../Systems/ShootSystem.hpp"
#include "../Systems/OobDieSystem.hpp"
#include "../Systems/ExperienceSystem.hpp"
#include "../Systems/DeckSystem.hpp"
#include "../Systems/AiSystem.hpp"
#include "../Systems/CutsceneSystem.hpp"
#include "../Systems/BossHudSystem.hpp"
#include "../../Resources/Game.hpp"

namespace TouhouFanGame::ECS::Factory
{
	const std::vector<std::function<System *(Core &)>> SystemFactory::_builders{
		[](Core &core){ return new Systems::DisplayableSystem(core); },
		[](Core &core){ return new Systems::ControllableSystem(core); },
		[](Core &core){ return new Systems::MovableSystem(core); },
		[](Core &core){ return new Systems::BlockedByTerrainSystem(core); },
		[](Core &core){ return new Systems::HealthSystem(core); },
		[](Core &core){ return new Systems::ManaSystem(core); },
		[](Core &core){ return new Systems::UselessSystem(core, "Position"); },
		[](Core &core){ return new Systems::UselessSystem(core, "Name"); },
		[](Core &core){ return new Systems::UselessSystem(core, "Inventory"); },
		[](Core &core){ return new Systems::UselessSystem(core, "Interact", {"Collider"}); },
		[](Core &core){ return new Systems::PlayerHUDSystem(core); },
		[](Core &core){ return new Systems::CollisionSystem(core); },
		[](Core &core){ return new Systems::DialogSystem(core); },
		[](Core &core){ return new Systems::ShootSystem(core); },
		[](Core &core){ return new Systems::OOBDieSystem(core); },
		[](Core &core){ return new Systems::ExperienceSystem(core); },
		[](Core &core){ return new Systems::DeckSystem(core); },
		[](Core &core){ return new Systems::AISystem(core); },
		[](Core &core){ return new Systems::CutsceneSystem(core); },
		[](Core &core){ return new Systems::BossHUDSystem(core); },
		[](Core &core){ return new Systems::UselessSystem(core, "Collider", {"Position"}); },
	};

	void SystemFactory::buildAll(Core &core, std::vector<std::unique_ptr<System>> &buffer)
	{
		for (auto &fc : SystemFactory::_builders)
			buffer.emplace_back(fc(core));
	}
}