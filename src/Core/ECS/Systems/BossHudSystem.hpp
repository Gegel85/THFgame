//
// Created by Gegel85 on 21/04/2020.
//

#ifndef THFGAME_BOSSHUDSYSTEM_HPP
#define THFGAME_BOSSHUDSYSTEM_HPP


#include "../System.hpp"

namespace TouhouFanGame::ECS::Systems
{
	//! @brief Updates Entity having a PlayerHUDComponent
	class BossHUDSystem : public System {
	public:
		BossHUDSystem(Core &core);

		void updateEntity(const std::shared_ptr<Entity> &) override;
	};
};


#endif //THFGAME_BOSSHUDSYSTEM_HPP
