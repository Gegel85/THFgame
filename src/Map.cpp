//
// Created by Gegel85 on 26/09/2019.
//

#include <cmath>
#include <cstring>
#include "Map.hpp"
#include "Game.hpp"
#include "Exceptions.hpp"
#include "ECS/Components/PositionComponent.hpp"

namespace TouhouFanGame
{
	void Map::serialize(std::ostream &stream) const
	{}

	void Map::unserialize(std::istream &stream)
	{
		char byte;

		this->_tileMap.clear();
		do {
			stream.read(&byte, 1);
			if (byte)
				this->_tileMap.push_back(byte);
		} while (byte);

		stream.read(&byte, 1);
		this->_tileSize = byte;

		stream.read(&byte, 1);
		this->_size.x = byte;

		stream.read(&byte, 1);
		this->_size.y = byte;

		std::memset(this->_links, 0, sizeof(this->_links));
		for (auto &link : this->_links)
			for (int j = 0; j < 2; j++) {
				stream.read(&byte, 1);
				link <<= 8;
				link |= byte;
			}

		for (unsigned y = 0; y < this->_size.y; y++)
			for (unsigned x = 0; x < this->_size.x; x++) {
				stream.read(&byte, 1);
				this->_objects.push_back(byte);
			}

		if (this->_core.getEntityByName("Player").empty())
			this->_core.makeEntity("Player");
	}

	void Map::update()
	{
		this->_core.update();

		auto &pos = this->_getPlayerPosition();
		auto size = this->_getPlayerSize();

		if (pos.x < size.x / -2.) {
			this->loadFromFile("assets/maps/map_" + std::to_string(this->_links[Input::LEFT]) + ".map");
			pos.x = this->_size.x * this->_tileSize - size.x / 2.;
		} else if (pos.y < size.y / -2.) {
			this->loadFromFile("assets/maps/map_" + std::to_string(this->_links[Input::UP]) + ".map");
			pos.y = this->_size.y * this->_tileSize - size.y / 2.;
		} else if (pos.x + size.x / 2. > this->_size.x * this->_tileSize) {
			this->loadFromFile("assets/maps/map_" + std::to_string(this->_links[Input::RIGHT]) + ".map");
			pos.x = size.x / -2.;
		} else if (pos.y + size.y / 2. > this->_size.y * this->_tileSize) {
			this->loadFromFile("assets/maps/map_" + std::to_string(this->_links[Input::DOWN]) + ".map");
			pos.y = size.y / -2.;
		}
	}

	void Map::clear()
	{
		this->_core.clear();
		this->_objects.clear();
	}

	unsigned char Map::getObjectAt(int x, int y) const
	{
		if (x < 0)
			return 0x00;
		if (y < 0)
			return 0x00;
		if (x / this->_tileSize >= this->_size.x)
			return 0x00;
		if (y / this->_tileSize >= this->_size.y)
			return 0x00;
		return this->_objects.at(this->_size.x * (y / this->_tileSize) + (x / this->_tileSize));
	}

	unsigned char Map::getTileSize() const
	{
		return this->_tileSize;
	}

	unsigned char Map::getObjectAt(sf::Vector2f pos) const
	{
		return this->getObjectAt(pos.x, pos.y);
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
		pos.x /= this->_tileSize;
		pos.y /= this->_tileSize;
		size.x = ceil(size.x / static_cast<float>(this->_tileSize));
		size.y = ceil(size.y / static_cast<float>(this->_tileSize));

		for (unsigned y = pos.y < 0 ? 0 : pos.y; y < pos.y + size.y && y < this->_size.y; y++) {
			for (unsigned x = pos.x < 0 ? 0 : pos.x; x < pos.x + size.x && x < this->_size.x; x++) {
				game.resources.screen->draw(
					game.resources.textures.at(this->_tileMap),
					{
						static_cast<float>(x * this->_tileSize),
						static_cast<float>(y * this->_tileSize)
					},
					{
						static_cast<int>((this->_objects.at(x + y * this->_size.x) & 0x7F) * this->_tileSize),
						0,
						static_cast<int>(this->_tileSize),
						static_cast<int>(this->_tileSize)
					}
				);
			}
		}

		this->_cameraUpdated = false;
		game.resources.screen->renderEntities();
	}

	void Map::updateCameraPosition(sf::Vector2f focusPoint)
	{
		this->_cameraUpdated = true;
		this->_cameraCenter.x = Map::_updateCameraCenter(this->_size.x * this->_tileSize, game.resources.screen->getSize().x, focusPoint.x);
		this->_cameraCenter.y = Map::_updateCameraCenter(this->_size.y * this->_tileSize, game.resources.screen->getSize().y, focusPoint.y);
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

	ECS::Entity &Map::_getPlayer()
	{
		std::vector<std::reference_wrapper<ECS::Entity>> players = this->_core.getEntityByName("Player");

		if (players.size() != 1)
			throw CorruptedMapException(
				"There should be a single player in the game but " +
				std::to_string(players.size()) + " were found"
			);

		return players.back().get();
	}

	sf::Vector2u &Map::_getPlayerSize()
	{
		return this->_getPlayer().getComponent("Position").to<ECS::Components::PositionComponent>().size;
	}

	sf::Vector2f &Map::_getPlayerPosition()
	{
		return this->_getPlayer().getComponent("Position").to<ECS::Components::PositionComponent>().position;
	}
}