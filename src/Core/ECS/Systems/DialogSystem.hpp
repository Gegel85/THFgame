//
// Created by Gegel85 on 06/01/2020.
//

#ifndef THFGAME_DIALOGSYSTEM_HPP
#define THFGAME_DIALOGSYSTEM_HPP


#include "../System.hpp"

namespace TouhouFanGame::ECS::Systems
{
	class DialogSystem : public System {
	public:
		//! @param core The Core the System is in.
		DialogSystem(Core &core);
		void updateEntity(const std::shared_ptr<Entity> &entity) override;
	};
}


#endif //THFGAME_DIALOGSYSTEM_HPP
