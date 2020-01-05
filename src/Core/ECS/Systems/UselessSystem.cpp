//
// Created by Gegel85 on 12/10/2019.
//

#include "UselessSystem.hpp"

namespace TouhouFanGame::ECS::Systems
{
	UselessSystem::UselessSystem(TouhouFanGame::ECS::Core &core, const std::string &fakeName, const std::vector<std::string> &&dependencies) :
		System(core, std::move(fakeName), std::move(dependencies))
	{
	}

	void UselessSystem::updateEntity(TouhouFanGame::ECS::Entity &)
	{}
}