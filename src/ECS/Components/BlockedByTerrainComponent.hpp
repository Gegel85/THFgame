//
// Created by Gegel85 on 12/10/2019.
//

#ifndef THFGAME_BLOCKEDBYTERRAINCOMPONENT_HPP
#define THFGAME_BLOCKEDBYTERRAINCOMPONENT_HPP


#include "../../Map.hpp"

namespace TouhouFanGame::ECS::Components
{
	class BlockedByTerrainComponent : public Component {
	public:
		Map &map;

		explicit BlockedByTerrainComponent(Map &map);
		~BlockedByTerrainComponent() override = default;
		void serialize(std::ostream &) const override;
		void unserialize(std::istream &) override;
	};
}


#endif //THFGAME_BLOCKEDBYTERRAINCOMPONENT_HPP
