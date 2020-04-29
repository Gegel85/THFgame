//
// Created by Gegel85 on 29/04/2020.
//

#ifndef THFGAME_PROJECTILESYSTEM_HPP
#define THFGAME_PROJECTILESYSTEM_HPP


#include "../System.hpp"

namespace TouhouFanGame::ECS::Systems
{
	//! @brief Updates Entity having a PlayerHUDComponent
	class ProjectileSystem : public System {
	public:
		ProjectileSystem(Core &core);
		void updateEntity(const std::shared_ptr<Entity> &) override;
	};
}


#endif //THFGAME_PROJECTILESYSTEM_HPP
