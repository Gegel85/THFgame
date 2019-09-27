//
// Created by Gegel85 on 28/09/2019.
//

#include "SystemFactory.hpp"

namespace TouhouFanGame::ECS::Factory
{
	const std::vector<std::function<System *(Core &)>> SystemFactory::_builders{
		[](Core &core){ return new Systems::DisplayableSystem(core); }
	};

	void SystemFactory::buildAll(TouhouFanGame::ECS::Core &core, std::vector<std::unique_ptr<System>> &buffer)
	{
		for (auto &fc : _builders)
			buffer.emplace_back(fc(core));
	}
}