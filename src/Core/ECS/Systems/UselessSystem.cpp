//
// Created by Gegel85 on 12/10/2019.
//

#include "UselessSystem.hpp"

namespace TouhouFanGame::ECS::Systems
{
	UselessSystem::UselessSystem(TouhouFanGame::ECS::Core &core, const std::string &fakeName) :
		System(core, std::move(fakeName), {})
	{
	}

	void UselessSystem::updateEntity(TouhouFanGame::ECS::Entity &)
	{}
}