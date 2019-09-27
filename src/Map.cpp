//
// Created by Gegel85 on 26/09/2019.
//

#include <cmath>
#include <iostream>
#include "Map.hpp"
#include "Game.hpp"
#include "Exceptions.hpp"
#include "ECS/Components/PositionComponent.hpp"

namespace TouhouFanGame
{
	void Map::serialize(std::ostream &stream)
	{}

	void Map::unserialize(std::istream &stream)
	{
		this->_tileMap = "tilemap1";
		this->_size = {64, 64};

		for (unsigned y = 0; y < this->_size.y; y++)
			for (unsigned x = 0; x < this->_size.x; x++)
				this->_objects.push_back(y % 4);

		if (this->_core.getEntityByName("Player").empty())
			this->_core.makeEntity("Player");
	}

	void Map::update()
	{
		this->_core.update();
	}

	void Map::clear()
	{
		this->_core.clear();
		this->_objects.clear();
	}

	void Map::loadFromFile(const std::string &path)
	{
		std::ifstream stream{path};

		logger.debug("Loading map " + path);
		if (stream.fail())
			throw CorruptedMapException("Cannot open file " + path);

		this->unserialize(stream);
	}

	void Map::render()
	{
		if (!this->_cameraUpdated) {
			sf::Vector2f pos = this->_getPlayerPosition();

			pos.x += PLAYER_SIZE / 2;
			pos.y += PLAYER_SIZE / 2;
			this->updateCameraPosition(pos);
		}

		sf::Vector2u size = game.resources.screen->getSize();
		sf::Vector2f pos = this->_cameraCenter;

		pos.x -= size.x / 2.;
		pos.y -= size.y / 2.;
		game.resources.screen->setCamera(pos);
		pos.x /= TILE_SIZE;
		pos.y /= TILE_SIZE;
		size.x = ceil(size.x / static_cast<float>(TILE_SIZE));
		size.y = ceil(size.y / static_cast<float>(TILE_SIZE));

		for (unsigned y = pos.y < 0 ? 0 : pos.y; y < pos.y + size.y && y < this->_size.y; y++) {
			for (unsigned x = pos.x < 0 ? 0 : pos.x; x < pos.x + size.x && x < this->_size.x; x++) {
				game.resources.screen->draw(
					game.resources.textures.at(this->_tileMap),
					{
						static_cast<float>(x * TILE_SIZE),
						static_cast<float>(y * TILE_SIZE)
					},
					{
						this->_objects[x + y * this->_size.x] * TILE_SIZE,
						0,
						TILE_SIZE,
						TILE_SIZE
					}
				);
			}
		}

		game.resources.screen->draw(
			game.resources.textures.at(this->_tileMap),
			{
				this->_getPlayerPosition().x,
				this->_getPlayerPosition().y
			},
			{
				24,
				-8,
				TILE_SIZE * 2,
				TILE_SIZE * 2
			}
		);

		this->_cameraUpdated = false;
		game.resources.screen->renderEntities();
	}

	void Map::updateCameraPosition(sf::Vector2f focusPoint)
	{
		this->_cameraUpdated = true;
		this->_cameraCenter.x = this->_updateCameraCenter(this->_size.x * TILE_SIZE, game.resources.screen->getSize().x, focusPoint.x);
		this->_cameraCenter.y = this->_updateCameraCenter(this->_size.y * TILE_SIZE, game.resources.screen->getSize().y, focusPoint.y);
	}

	float Map::_updateCameraCenter(float size, float screenSize, float focusPoint)
	{
		if (size <= screenSize)
			return size / 2;

		if (focusPoint < screenSize / 2)
			return screenSize / 2;

		if (focusPoint > size - screenSize / 2)
			return size - screenSize / 2;

		return focusPoint;
	}

	ECS::Entity& Map::_getPlayer()
	{
		std::vector<std::reference_wrapper<ECS::Entity>> players = this->_core.getEntityByName("Player");

		if (players.size() != 1)
			throw CorruptedMapException(
				"There should be a single player in the game but " +
				std::to_string(players.size()) + " were found"
			);

		return players.back().get();
	}

	sf::Vector2f Map::_getPlayerPosition()
	{
		return reinterpret_cast<ECS::Components::PositionComponent &>(this->_getPlayer().getComponent("Position")).position;
	}
}