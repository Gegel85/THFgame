//
// Created by Gegel85 on 12/10/2019.
//

#include <iostream>
#include <cmath>
#include "BlockedByTerrainSystem.hpp"
#include "../Components/PositionComponent.hpp"
#include "../Components/MovableComponent.hpp"
#include "../Components/BlockedByTerrainComponent.hpp"
#include "../../Input.hpp"

namespace TouhouFanGame::ECS::Systems
{
	BlockedByTerrainSystem::BlockedByTerrainSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "BlockedByTerrain", {"Movable", "Position"})
	{}

	void BlockedByTerrainSystem::_pushEntity(TouhouFanGame::ECS::Components::PositionComponent &pos, float x, float y, unsigned char tileSize, unsigned char &dir, float speed)
	{
		sf::Vector2<double> wallPos{
			pos.position.x + x - std::fmod(pos.position.x + x, tileSize),
			pos.position.y + y - std::fmod(pos.position.y + x, tileSize),
		};

		if (
			pos.position.x + pos.size.x + (speed * ((dir & TO_DIR(Input::RIGHT)) != 0)) < wallPos.x ||
			pos.position.x - (speed * ((dir & TO_DIR(Input::LEFT)) != 0)) > wallPos.x + tileSize ||
			pos.position.y + pos.size.y + (speed * ((dir & TO_DIR(Input::DOWN)) != 0)) < wallPos.y ||
			pos.position.y - (speed * ((dir & TO_DIR(Input::UP)) != 0)) > wallPos.y + tileSize
		)
			return;

		if (pos.position.y + pos.size.y > wallPos.y && pos.position.y < wallPos.y + tileSize) {
			if (pos.position.x + pos.size.x <= wallPos.x && (dir & TO_DIR(Input::RIGHT)))
				pos.position.x = wallPos.x - pos.size.x - speed;
			else if (pos.position.x >= wallPos.x + tileSize && (dir & TO_DIR(Input::LEFT)))
				pos.position.x = wallPos.x + tileSize + speed;
		}

		if (pos.position.x + pos.size.x > wallPos.x && pos.position.x < wallPos.x + tileSize) {
			if (pos.position.y + pos.size.y <= wallPos.y && (dir & TO_DIR(Input::DOWN)))
				pos.position.y = wallPos.y - pos.size.y - speed;
			else if (pos.position.y >= wallPos.y + tileSize && (dir & TO_DIR(Input::UP)))
				pos.position.y = wallPos.y + tileSize + speed;
		}
	}

	void BlockedByTerrainSystem::updateEntity(TouhouFanGame::ECS::Entity &entity)
	{
		auto &pos = entity.getComponent("Position").to<Components::PositionComponent>();
		auto &mov = entity.getComponent("Movable").to<Components::MovableComponent>();
		auto &block = entity.getComponent("BlockedByTerrain").to<Components::BlockedByTerrainComponent>();
		unsigned char tileSize = block.map.getTileSize();
		unsigned char newDir = mov.dir;
		float end = mov.speed - std::fmod(mov.speed, tileSize) + tileSize;

		for (float x = -end; x < pos.size.x + end; x += tileSize)
			for (float y = -end; y < pos.size.y + end; y += tileSize)
				if (block.map.getObjectAt({pos.position.x + x, pos.position.y + y}) & 0x80U)
					BlockedByTerrainSystem::_pushEntity(pos, x, y, tileSize, newDir, mov.speed);

		if (newDir)
			mov.dir = newDir;
		else
			mov.speed = 0;
	}
}