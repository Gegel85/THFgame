//
// Created by Gegel85 on 12/10/2019.
//

#ifndef THFGAME_BLOCKEDBYTERRAINSYSTEM_HPP
#define THFGAME_BLOCKEDBYTERRAINSYSTEM_HPP


#include "../Core.hpp"
#include "../Entity.hpp"
#include "../Components/PositionComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	class BlockedByTerrainSystem : public System {
	public:
		BlockedByTerrainSystem(Core &core);
		void pushEntity(Components::PositionComponent &pos, float x, float y, unsigned char tileSize, unsigned char &dir, float speed);
		void updateEntity(Entity &) override;
	};
}


#endif //THFGAME_BLOCKEDBYTERRAINSYSTEM_HPP
