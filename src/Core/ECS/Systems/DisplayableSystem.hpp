//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_DISPLAYABLESYSTEM_HPP
#define THFGAME_DISPLAYABLESYSTEM_HPP


#include "../System.hpp"

namespace TouhouFanGame::ECS::Systems
{
	//! @brief Updates Entity having a DisplayableComponent
	class DisplayableSystem : public System {
	public:
		//! @param _parent The Core the System is in.
		explicit DisplayableSystem(Core &_parent);
		void updateEntity(const std::shared_ptr<Entity> &) override;
	};
}


#endif //THFGAME_DISPLAYABLESYSTEM_HPP
