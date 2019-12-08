//
// Created by Gegel85 on 12/10/2019.
//

#ifndef THFGAME_BLOCKEDBYTERRAINCOMPONENT_HPP
#define THFGAME_BLOCKEDBYTERRAINCOMPONENT_HPP


#include "../../Map.hpp"
#include "BasicSerializeComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	//! @brief Given to Entity that are blocked by Map terrain.
	class BlockedByTerrainComponent : public BasicSerializeComponent {
	public:
		//! @brief The Map the Entity is in.
		Map &map;

		explicit BlockedByTerrainComponent(Map &map);
		~BlockedByTerrainComponent() override = default;
	};
}


#endif //THFGAME_BLOCKEDBYTERRAINCOMPONENT_HPP
