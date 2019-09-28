//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_CONTROLLABLESYSTEM_HPP
#define THFGAME_CONTROLLABLESYSTEM_HPP


#include "../System.hpp"
#include "../../Input.hpp"

namespace TouhouFanGame::ECS::Systems
{
	class ControllableSystem : public System {
	public:
		ControllableSystem(Core &core);
		void updateEntity(Entity &entity) override;
	};
}


#endif //THFGAME_CONTROLLABLESYSTEM_HPP
