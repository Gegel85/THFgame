//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_MOVABLESYSTEM_HPP
#define THFGAME_MOVABLESYSTEM_HPP


#include "../System.hpp"

namespace TouhouFanGame::ECS::Systems
{
	//! @brief Updates Entity having a MovableComponent
	class MovableSystem : public System {
	public:
		//! @param core The Core the System is in.
		MovableSystem(Core &core);
		void updateEntity(Entity &) override;
	};
}


#endif //THFGAME_MOVABLESYSTEM_HPP
