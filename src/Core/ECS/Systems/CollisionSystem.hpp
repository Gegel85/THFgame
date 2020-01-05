//
// Created by Gegel85 on 05/01/2020.
//

#ifndef THFGAME_COLLISIONSYSTEM_HPP
#define THFGAME_COLLISIONSYSTEM_HPP


#include "../System.hpp"

namespace TouhouFanGame::ECS::Systems
{
	//! @brief Updates Entity having a CollisionComponent
	class CollisionSystem : public System {
	public:
		//! @param core The Core the System is in.
		CollisionSystem(Core &core);
		void updateEntity(Entity &entity) override;
	};
}


#endif //THFGAME_COLLISIONSYSTEM_HPP
