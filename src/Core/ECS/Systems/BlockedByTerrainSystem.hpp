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
	//! @brief Updates Entity having a BlockedByTerrainComponent
	class BlockedByTerrainSystem : public System {
	private:
		//! @brief Used to push an entity out of a solid tile.
		//! @param pos The position of the Entity to update.
		//! @param x The X coordinate of the tile.
		//! @param y The Y coordinate of the tile.
		//! @param tileSize The size of a single tile.
		//! @param dir The direction of the Entity to update.
		//! @param speed The speed
		static void _pushEntity(Components::PositionComponent &pos, float x, float y, unsigned char tileSize, double &dir, float &speed);

	public:
		//! @param core The Core the System is in.
		BlockedByTerrainSystem(Core &core);
		void updateEntity(const std::shared_ptr<Entity> &) override;
	};
}


#endif //THFGAME_BLOCKEDBYTERRAINSYSTEM_HPP
