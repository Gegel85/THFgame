//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_DISPLAYABLESYSTEM_HPP
#define THFGAME_DISPLAYABLESYSTEM_HPP


#include "../System.hpp"

namespace TouhouFanGame::ECS::Systems
{
	class DisplayableSystem : public System {
	public:
		explicit DisplayableSystem(Core &_parent);
		void updateEntity(Entity &) override;
	};
}


#endif //THFGAME_DISPLAYABLESYSTEM_HPP
