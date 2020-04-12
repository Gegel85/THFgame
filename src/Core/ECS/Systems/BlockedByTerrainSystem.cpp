//
// Created by Gegel85 on 12/10/2019.
//

#include <iostream>
#include <cmath>
#include "BlockedByTerrainSystem.hpp"
#include "../Components/PositionComponent.hpp"
#include "../Components/MovableComponent.hpp"
#include "../Components/BlockedByTerrainComponent.hpp"
#include "../../Input/Input.hpp"

namespace TouhouFanGame::ECS::Systems
{
	BlockedByTerrainSystem::BlockedByTerrainSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "BlockedByTerrain", {"Movable", "Position"})
	{}

	void BlockedByTerrainSystem::_pushEntity(TouhouFanGame::ECS::Components::PositionComponent &pos, float x, float y, unsigned char tileSize, double &dir, float &speed)
	{
		Vector2<double> wallPos{
			pos.position.x + x - std::fmod(pos.position.x + x, tileSize),
			pos.position.y + y - std::fmod(pos.position.y + x, tileSize),
		};
		Vector2<double> vec{
			cos(dir),
			sin(dir),
		};

		if (
			pos.position.x + pos.size.x + speed * vec.x * (vec.x > 0) < wallPos.x ||
			pos.position.x - speed * vec.x * (vec.x < 0) > wallPos.x + tileSize ||
			pos.position.y + pos.size.y + speed * vec.y * (vec.y > 0) < wallPos.y ||
			pos.position.y - speed * vec.y * (vec.y < 0) > wallPos.y + tileSize
		)
			return;

		if (pos.position.y + pos.size.y > wallPos.y && pos.position.y < wallPos.y + tileSize) {
			if (pos.position.x + pos.size.x <= wallPos.x && vec.x > 0) {
				pos.position.x = wallPos.x - pos.size.x - speed * vec.x;
				dir = vec.y > 0 ? -M_PI_2 : M_PI_2;
				vec.x = 0;
			} else if (pos.position.x >= wallPos.x + tileSize && vec.x < 0) {
				pos.position.x = wallPos.x + tileSize + speed * vec.x;
				dir = vec.y > 0 ? -M_PI_2 : M_PI_2;
				vec.x = 0;
			}
		}

		if (pos.position.x + pos.size.x > wallPos.x && pos.position.x < wallPos.x + tileSize) {
			if (pos.position.y + pos.size.y <= wallPos.y && vec.y > 0) {
				pos.position.y = wallPos.y - pos.size.y - speed * vec.y;
				dir = vec.x > 0 ? 0 : M_PI;
				vec.y = 0;
			} else if (pos.position.y >= wallPos.y + tileSize && vec.y < 0) {
				pos.position.y = wallPos.y + tileSize + speed * vec.y;
				dir = vec.x > 0 ? 0 : M_PI;
				vec.y = 0;
			}
		}

		if (!vec.x && !vec.y)
			speed = 0;
	}

	void BlockedByTerrainSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &pos = entity->getComponent(Position);
		auto &mov = entity->getComponent(Movable);
		auto &block = entity->getComponent(BlockedByTerrain);
		unsigned char tileSize = block.map.getTileSize();
		float end = mov.speed - std::fmod(mov.speed, tileSize) + tileSize;

		//TODO: Fix collision when going DOWN
		for (float x = -end; x < pos.size.x + end; x += tileSize)
			for (float y = -end; y < pos.size.y + end; y += tileSize)
				if (block.map.getObjectAt({pos.position.x + x, pos.position.y + y}) & 0x80U)
					BlockedByTerrainSystem::_pushEntity(pos, x, y, tileSize, mov.angleDir, mov.speed);

	}
}