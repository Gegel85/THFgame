//
// Created by Gegel85 on 16/04/2020.
//

#ifndef THFGAME_CUTSCENESYSTEM_HPP
#define THFGAME_CUTSCENESYSTEM_HPP


#include "../System.hpp"

namespace TouhouFanGame::ECS::Systems
{
	class CutsceneSystem : public System {
	public:
		//! @param core The Core the System is in.
		CutsceneSystem(Core &core);
		void updateEntity(const std::shared_ptr<Entity> &entity) override;
	};
}


#endif //THFGAME_CUTSCENESYSTEM_HPP
