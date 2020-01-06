//
// Created by Gegel85 on 18/11/2019.
//

#ifndef THFGAME_PLAYERHUDSYSTEM_HPP
#define THFGAME_PLAYERHUDSYSTEM_HPP


#include "../System.hpp"

namespace TouhouFanGame::ECS::Systems
{
	//! @brief Updates Entity having a PlayerHUDComponent
	class PlayerHUDSystem : public System {
	public:
		PlayerHUDSystem(Core &core);
		void updateEntity(const std::shared_ptr<Entity> &) override;
	};
}


#endif //THFGAME_PLAYERHUDSYSTEM_HPP
