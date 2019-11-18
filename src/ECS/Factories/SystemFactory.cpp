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

namespace TouhouFanGame::ECS::Factory
{
	void SystemFactory::buildAll(TouhouFanGame::ECS::Core &core, std::vector<std::unique_ptr<System>> &buffer)
	{
		const std::vector<std::function<System *(Core &)>> _builders{
			[](Core &core){ return new Systems::DisplayableSystem(core); },
			[](Core &core){ return new Systems::ControllableSystem(core); },
			[](Core &core){ return new Systems::MovableSystem(core); },
			[](Core &core){ return new Systems::BlockedByTerrainSystem(core); },
			[](Core &core){ return new Systems::HealthSystem(core); },
			[](Core &core){ return new Systems::ManaSystem(core); },
			[](Core &core){ return new Systems::UselessSystem(core, "Position"); },
		};

		for (auto &fc : _builders)
			buffer.emplace_back(fc(core));
	}
}