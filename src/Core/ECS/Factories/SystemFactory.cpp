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
	const std::vector<std::function<System *(Game &, Core &)>> SystemFactory::_builders{
		[](Game &    , Core &core){ return new Systems::DisplayableSystem(core); },
		[](Game &    , Core &core){ return new Systems::ControllableSystem(core); },
		[](Game &    , Core &core){ return new Systems::MovableSystem(core); },
		[](Game &    , Core &core){ return new Systems::BlockedByTerrainSystem(core); },
		[](Game &    , Core &core){ return new Systems::HealthSystem(core); },
		[](Game &    , Core &core){ return new Systems::ManaSystem(core); },
		[](Game &    , Core &core){ return new Systems::UselessSystem(core, "Position"); },
		[](Game &    , Core &core){ return new Systems::UselessSystem(core, "Name"); },
		[](Game &    , Core &core){ return new Systems::UselessSystem(core, "Inventory"); },
		[](Game &    , Core &core){ return new Systems::UselessSystem(core, "Interact", {"Collider"}); },
		[](Game &    , Core &core){ return new Systems::PlayerHUDSystem(core); },
		[](Game &    , Core &core){ return new Systems::CollisionSystem(core); },
		[](Game &    , Core &core){ return new Systems::DialogSystem(core); },
		[](Game &    , Core &core){ return new Systems::ShootSystem(core); },
		[](Game &    , Core &core){ return new Systems::OOBDieSystem(core); },
		[](Game &    , Core &core){ return new Systems::ExperienceSystem(core); },
		[](Game &    , Core &core){ return new Systems::DeckSystem(core); },
		[](Game &    , Core &core){ return new Systems::AISystem(core); },
		[](Game &    , Core &core){ return new Systems::CutsceneSystem(core); },
		[](Game &    , Core &core){ return new Systems::BossHUDSystem(core); },
		[](Game &    , Core &core){ return new Systems::UselessSystem(core, "Collider", {"Position"}); },
	};

	void SystemFactory::buildAll(Game &game, Core &core, std::vector<std::unique_ptr<System>> &buffer)
	{
		for (auto &fc : SystemFactory::_builders)
			buffer.emplace_back(fc(game, core));
	}
}