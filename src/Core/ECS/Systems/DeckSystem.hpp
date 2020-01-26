//
// Created by Gegel85 on 26/01/2020.
//

#ifndef THFGAME_DECKSYSTEM_HPP
#define THFGAME_DECKSYSTEM_HPP


#include "../Core.hpp"
#include "../Entity.hpp"
#include "../Components/PositionComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	//! @brief Updates Entity having a DeckSystgemComponent
	class DeckSystem : public System {
	public:
		//! @param core The Core the System is in.
		DeckSystem(Core &core);
		void updateEntity(const std::shared_ptr<Entity> &) override;
	};
}


#endif //THFGAME_DECKSYSTEM_HPP
