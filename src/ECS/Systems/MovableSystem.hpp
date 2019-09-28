//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_MOVABLESYSTEM_HPP
#define THFGAME_MOVABLESYSTEM_HPP


#include "../System.hpp"

namespace TouhouFanGame::ECS::Systems
{
	class MovableSystem : public System {
	public:
		MovableSystem(Core &core);
		void updateEntity(Entity &) override;
	};
}


#endif //THFGAME_MOVABLESYSTEM_HPP
