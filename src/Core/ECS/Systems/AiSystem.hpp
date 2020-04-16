//
// Created by Gegel85 on 16/04/2020.
//

#ifndef THFGAME_AISYSTEM_HPP
#define THFGAME_AISYSTEM_HPP


#include "ControllableSystem.hpp"

namespace TouhouFanGame::ECS::Systems
{
	class AISystem : public ControllableSystem {
	public:
		//! @param core The Core the System is in.
		AISystem(Core &core);
		void updateEntity(const std::shared_ptr<Entity> &entity) override;
	};
}


#endif //THFGAME_AISYSTEM_HPP
