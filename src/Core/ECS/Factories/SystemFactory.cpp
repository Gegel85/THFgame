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
		[](Core &core){ return new Systems::PlayerHUDSystem(core); },
	};

	void SystemFactory::buildAll(TouhouFanGame::ECS::Core &core, std::vector<std::unique_ptr<System>> &buffer)
	{
		for (auto &fc : _builders)
			buffer.emplace_back(fc(core));
	}
}