//
// Created by Gegel85 on 12/10/2019.
//

#ifndef THFGAME_USELESSSYSTEM_HPP
#define THFGAME_USELESSSYSTEM_HPP


#include "../Core.hpp"
#include "../Entity.hpp"

namespace TouhouFanGame::ECS::Systems
{
	class UselessSystem : public System {
	public:
		UselessSystem(Core &core, const std::string &fakeName);
		void updateEntity(Entity &) override;
	};
}


#endif //THFGAME_USELESSSYSTEM_HPP
