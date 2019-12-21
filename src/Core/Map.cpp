//
// Created by Gegel85 on 26/09/2019.
//

#include <cmath>
#include <cstring>
#include "Map.hpp"
#include "Game.hpp"
#include "../Exceptions.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "../Utils.hpp"

namespace TouhouFanGame
{
	Map::Map(TouhouFanGame::Game &game) :
		_game(game),
		_core(game)
	{
	}

	Map::TpTrigger::TpTrigger(std::istream &stream) :
		location(_readInteger<unsigned short>(stream), _readInteger<unsigned short>(stream)),
		mapId(_readInteger<unsigned short>(stream)),
		mapSpawn(_readInteger<unsigned short>(stream), _readInteger<unsigned short>(stream))
	{
	}

	void Map::_serialize(std::ostream &stream) const
	{
		if (this->_path.empty()) {
			logger.error("Trying to serialize a not loaded map.");
			throw MapNotLoadedException();
		}
		stream << this->_path << '\0';
		stream << this->_core;
	}

	void Map::_serialize(const std::string &path)
	{
		logger.info("Saving map to " + path);
		Utils::makeDirectoryTree(path);

		std::ofstream stream{path};

		if (stream.fail()) {
			logger.error("Couldn't save map to " + path + ": " + strerror(errno));
			throw MapSavingFailureException(path + ": " + strerror(errno));
		}

		this->_serialize(stream);
		stream.close();
	}

	void Map::_unserialize(std::istream &stream)
	{
		std::getline(stream, this->_path, '\0');
		this->_loadFromFile(this->_path, false);
		stream >> this->_core;
	}

	void Map::_unserialize(const std::string &path)
	{
		logger.info("Loading saved map from " + path);

		std::ifstream  stream{path};

		if (stream.fail()) {
			logger.error("Cannot open saved map from " + path + ": " + strerror(errno));
			throw InvalidSavedMap(path + ": " + strerror(errno));
		}

		this->_unserialize(stream);
		stream.close();
	}

	void Map::_loadMap(unsigned short id)
	{
		try {
			this->_unserialize("saves/map_" + std::to_string(id) + ".sav");
			return;
		} catch (InvalidSavedMap &) {
		} catch (std::exception &e) {
			throw InvalidSavedMap(e.what());
		}

		this->_loadFromFile("assets/maps/map_" + std::to_string(id) + ".map");
		this->_id = id;
	}

	void Map::_savePlayer()
	{
		std::ofstream stream{"saves/map_player.sav"};

		if (stream.fail()) {
			logger.error("Couldn't save map to saves/map_player.sav: " + std::string(strerror(errno)));
			throw MapSavingFailureException("saves/map_player.sav: " + std::string(strerror(errno)));
		}
		stream << this->getPlayer() << " " << this->_id;
		stream.close();
	}

	void Map::saveMap()
	{
		logger.info("Saving game");
		this->_savePlayer();
		this->_serialize("saves/map_" + std::to_string(this->_id) + ".sav");
	}

	void Map::loadMap()
	{
		std::ifstream stream{"saves/map_player.sav"};

		logger.info("Loading game");
		if (stream.fail()) {
			logger.error("Couldn't load map at saves/map_player.sav: " + std::string(strerror(errno)));
			if (errno != ENOENT)
				throw InvalidSavedMap("saves/map_player.sav: " + std::string(strerror(errno)));
			this->_loadMap(0);
			return;
		}
		this->reset();

		ECS::Entity &player = this->_core.registerEntity(new ECS::Entity());

		player.unserialize(this->_game, stream);
		stream >> this->_id;
		stream.close();
		player.setSerializable(false);
		this->_loadMap(this->_id);
	}

	void Map::update()
	{
		this->_core.update();

		auto &pos = this->_getPlayerPosition();
		auto size = this->_getPlayerSize();

		if (pos.x < size.x / -2.) {
			this->_serialize("saves/map_" + std::to_string(this->_id) + ".sav");
			this->_loadMap(this->_links[Input::LEFT]);
			pos.x = this->_size.x * this->_tileSize - size.x / 2.;
			this->_savePlayer();

		} else if (pos.y < size.y / -2.) {
			this->_serialize("saves/map_" + std::to_string(this->_id) + ".sav");
			this->_loadMap(this->_links[Input::UP]);
			pos.y = this->_size.y * this->_tileSize - size.y / 2.;
			this->_savePlayer();

		} else if (pos.x + size.x / 2. > this->_size.x * this->_tileSize) {
			this->_serialize("saves/map_" + std::to_string(this->_id) + ".sav");
			this->_loadMap(this->_links[Input::RIGHT]);
			pos.x = size.x / -2.;
			this->_savePlayer();

		} else if (pos.y + size.y / 2. > this->_size.y * this->_tileSize) {
			this->_serialize("saves/map_" + std::to_string(this->_id) + ".sav");
			this->_loadMap(this->_links[Input::DOWN]);
			pos.y = size.y / -2.;
			this->_savePlayer();

		}

		for (auto &trigger : this->_tpTriggers)
			if (
				-this->_tileSize < trigger.location.x && trigger.location.x < static_cast<int>(size.x + this->_tileSize) &&
				-this->_tileSize < trigger.location.y && trigger.location.y < static_cast<int>(size.y + this->_tileSize)
			) {
				this->_loadMap(trigger.mapId);
				pos = sf::Vector2f(trigger.mapSpawn.x, trigger.mapSpawn.y);
			}
	}

	void Map::reset()
	{
		try {
			this->_core.clear({this->getPlayer().getID()});
		} catch (CorruptedMapException &) {}
		this->_objects.clear();
		this->_tileMap.clear();
		this->_tpTriggers.clear();
		this->_path.clear();
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
		return this->_objects[this->_size.x * (y / this->_tileSize) + (x / this->_tileSize)];
	}

	unsigned char Map::getTileSize() const
	{
		return this->_tileSize;
	}

	unsigned char Map::getObjectAt(sf::Vector2f pos) const
	{
		return this->getObjectAt(pos.x, pos.y);
	}

	void Map::_loadFromStream(std::istream &stream, bool loadEntities)
	{
		logger.debug("Loading map");

		std::string music = _readString(stream);

		this->_game.resources.playMusic(music);
		this->_game.state.hud.setMusicName(this->_game.resources.musics.at(music).second);

		this->_tileMap = _readString(stream);
		logger.debug("Tilemap file is '" + this->_tileMap + "'");

		this->_tileSize = _readInteger<unsigned char>(stream);
		logger.debug("Tilesize is " + std::to_string(this->_tileSize));

		this->_size.x = _readInteger<unsigned short>(stream);
		this->_size.y = _readInteger<unsigned short>(stream);
		logger.debug("Map size is " + Utils::toString(this->_size) + " tiles");

		for (auto len = _readInteger<unsigned>(stream); len != 0; len--) {
			auto &result = this->_tpTriggers.emplace_back(stream);

			logger.debug(
				std::to_string(len) + " teleporters remaining ->"
				"Position: " + Utils::toString(result.location) +
				"Map: " + std::to_string(result.mapId) +
				"Spawn: " + Utils::toString(result.mapSpawn)
			);
		}

		std::memset(this->_links, 0, sizeof(this->_links));
		for (unsigned i = 0; i < 4; i++) {
			this->_links[i] = _readInteger<unsigned short>(stream);
			logger.debug("Link " + Input::actionToString(static_cast<Input::Action>(i)) + " is to map " + std::to_string(this->_links[i]));
		}

		logger.debug("Fetching objects");
		for (unsigned y = 0; y < this->_size.y; y++)
			for (unsigned x = 0; x < this->_size.x; x++)
				this->_objects.push_back(_readInteger<unsigned char>(stream));

		if (loadEntities) {
			logger.debug("Loading entities");
			stream >> this->_core;

			if (this->_core.getEntityByName("Player").empty())
				this->_core.makeEntity("Player");
		}
		logger.debug("Operation completed");
	}

	void Map::_loadFromFile(std::string path, bool loadEntities)
	{
		std::ifstream stream{path};

		logger.info("Loading map " + path);
		if (stream.fail()) {
			logger.error("Cannot load map " + path + ": " + strerror(errno));
			throw CorruptedMapException("Cannot open file " + path + ": " + strerror(errno));
		}

		this->reset();
		this->_loadFromStream(stream, loadEntities);
		this->_path = path;
	}

	void Map::render()
	{
		if (!this->_cameraUpdated) {
			sf::Vector2f pos = this->_getPlayerPosition();

			pos.x += PLAYER_SIZE / 2;
			pos.y += PLAYER_SIZE / 2;
			this->updateCameraPosition(pos);
		}

		sf::Vector2u size = this->_game.resources.screen->getSize();
		sf::Vector2f pos = this->_cameraCenter;

		this->_game.resources.screen->setCameraCenter(pos);
		pos.x -= size.x / 2.;
		pos.y -= size.y / 2.;
		pos.x /= this->_tileSize;
		pos.y /= this->_tileSize;
		size.x = ceil(size.x / static_cast<float>(this->_tileSize));
		size.y = ceil(size.y / static_cast<float>(this->_tileSize));

		for (unsigned y = pos.y < 0 ? 0 : pos.y; y < pos.y + size.y && y < this->_size.y; y++) {
			for (unsigned x = pos.x < 0 ? 0 : pos.x; x < pos.x + size.x && x < this->_size.x; x++) {
				this->_game.resources.screen->draw(
					this->_game.resources.textures.at(this->_tileMap),
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
		this->_game.resources.screen->renderEntities();
	}

	void Map::updateCameraPosition(sf::Vector2f focusPoint)
	{
		this->_cameraUpdated = true;
		this->_cameraCenter.x = Map::_getCameraCenter(
			this->_size.x * this->_tileSize,
			this->_game.resources.screen->getSize().x - HUD_HORIZONTAL_SIZE,
			focusPoint.x
		) + HUD_HORIZONTAL_SIZE / 2;
		this->_cameraCenter.y = Map::_getCameraCenter(
			this->_size.y * this->_tileSize,
			this->_game.resources.screen->getSize().y - HUD_VERTICAL_SIZE,
			focusPoint.y
		) + HUD_VERTICAL_SIZE / 2;
	}

	float Map::_getCameraCenter(float size, float screenSize, float focusPoint)
	{
		if (size <= screenSize)
			return size / 2;

		if (focusPoint < screenSize / 2)
			return screenSize / 2;

		if (focusPoint > size - screenSize / 2)
			return size - screenSize / 2;

		return focusPoint;
	}

	ECS::Entity &Map::getPlayer()
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
		return this->getPlayer().getComponent("Position").to<ECS::Components::PositionComponent>().size;
	}

	sf::Vector2f &Map::_getPlayerPosition()
	{
		return this->getPlayer().getComponent("Position").to<ECS::Components::PositionComponent>().position;
	}
}
