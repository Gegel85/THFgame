//
// Created by Gegel85 on 12/10/2019.
//

#ifndef THFGAME_USELESSSYSTEM_HPP
#define THFGAME_USELESSSYSTEM_HPP


#include "../Core.hpp"
#include "../Entity.hpp"

namespace TouhouFanGame::ECS::Systems
{
	//! @brief A useless System meant for Component that don't need one.
	class UselessSystem : public System {
	public:
		//! @param core The Core the System is in.
		//! @param fakeName The name this System should have.
		UselessSystem(Core &core, const std::string &fakeName, const std::vector<std::string> &&dependencies = {});
		void updateEntity(Entity &) override;
	};
}


#endif //THFGAME_USELESSSYSTEM_HPP
