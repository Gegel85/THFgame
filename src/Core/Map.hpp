//
// Created by Gegel85 on 26/09/2019.
//

#ifndef THFGAME_MAP_HPP
#define THFGAME_MAP_HPP


#include <SFML/Audio.hpp>
#include "ECS/Core.hpp"
#include "NotCopyable.hpp"
#include "Exceptions.hpp"

#define PLAYER_SIZE 32

namespace TouhouFanGame
{
	//! @brief A map loaded by the game.
	class Map {
	private:
		//! @brief A trigger that teleports the player to another Map.
		struct TpTrigger {
			//! @brief The position of the trigger on the Map.
			sf::Vector2<unsigned short> location;

			//! @brief The Map to warp to.
			unsigned short mapId;

			//! @brief Where to place the player after teleporting it.
			sf::Vector2<unsigned short> mapSpawn;

			//! @brief Loads a trigger from the stream.
			TpTrigger(std::istream &stream);
		};

		//! @brief The Game this map is in.
		Game &_game;

		//! @brief Whether the camera has already been updated this frame.
		bool _cameraUpdated = false;

		//! @brief Whether borders are solid objects
		//! @note This will only make borders solid object
		bool _solidBorders = false;

		//! @brief The four border links.
		unsigned short _links[4] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};

		//! @brief The path to the currently loaded map.
		std::string _path;

		//! @brief The size of map (in tiles).
		sf::Vector2<unsigned short> _size;

		//! @brief The size in pixel of a single square tile.
		unsigned char _tileSize = 0;

		//! @brief The id of the texture in the Resources to use to render the tiles.
		std::string _tileMap;

		//! @brief The tiles of the map.
		//! @details bit 0-6 The texture offset to use.
		//!          bit 7   Is this object solid ?
		std::vector<unsigned char> _objects;

		//! @brief All the triggers on the map.
		std::vector<TpTrigger> _tpTriggers;

		//! @brief The ECS::Core linked to the map.
		//! @details Contains the entities on the map.
		ECS::Core _core;

		//! @brief The center of the camera.
		sf::Vector2f _cameraCenter;

		//! @brief The ID of the currently loaded map
		unsigned int _id;


		template<typename type>
		//! @brief Reads an integer MSB from a stream.
		static type _readInteger(std::istream &stream) {
			char byte;
			type result = 0;

			for (size_t i = 0; i < sizeof(result); i++) {
				if (stream.eof())
					throw CorruptedMapException("EOF reached");
				stream.read(&byte, 1);
				result = result << 8U | byte;
			}
			return result;
		}

		//! @brief Reads an integer MSB from a stream.
		static std::string _readString(std::istream &stream) {
			char byte;
			std::string result;

			do {
				if (stream.eof())
					throw CorruptedMapException("EOF reached");
				stream.read(&byte, 1);
				if (byte)
					result.push_back(byte);
			} while (byte);
			return result;
		}

		//! @brief Computes the center of the camera from the map size, the window size and a focus point.
		//! @param size The size of the map.
		//! @param screenSize The size of the window.
		//! @param focusPoint The focus point.
		//! @return The suggested camera center for this axis
		static float _getCameraCenter(float size, float screenSize, float focusPoint);

		//! @return The current position of the player on the map.
		//! @warning Throws if no player or multiple players are found.
		//! @throw CorruptedMapException
		sf::Vector2f &_getPlayerPosition();

		//! @return The current size of the player on the map.
		//! @warning Throws if no player or multiple players are found.
		//! @throw CorruptedMapException
		sf::Vector2u &_getPlayerSize();

		//! @brief Loads the map from the stream given.
		//! @param stream The stream to load the map from.
		//! @param loadEntities Whether we want to load the entities or not.
		void _loadFromStream(std::istream &stream, bool loadEntities = true);

		//! @brief Serialize a map to the stream.
		//! @param stream The stream to serialize the map to.
		void _serialize(std::ostream &stream) const;

		//! @brief Serialize the map to a file
		//! @param path The file to save to.
		//! @throw MapSavingFailureException
		void _serialize(const std::string &path);

		//! @brief Unserialize a map from the stream.
		//! @param stream The stream to unserialize the map from.
		void _unserialize(std::istream &stream);

		//! @brief Unserialize the map from a file
		//! @param path The file to load from.
		//! @throw CorruptedMapException
		void _unserialize(const std::string &path);

		//! @brief Loads the map from the stream given.
		//! @param path The path to the file to load the map from.
		//! @param loadEntities Whether we want to load the entities or not.
		//! @throw CorruptedMapException
		void _loadFromFile(std::string path, bool loadEntities = true);

		//! @brief Load a map from it's ID.
		//! @throw InvalidSavedMap
		//! @throw CorruptedMapException
		void _loadMap(unsigned short id);

		//! @brief Saves the player Entity and the map it is on.
		void _savePlayer();

	public:
		Map(Game &game);

		//! @return The size in pixel of a square tile
		unsigned char getTileSize() const;

		//! @brief Get the object at position x y.
		//! @param x Horizontal position.
		//! @param y Vertical position.
		//! @return The object or 00 if out of bound.
		unsigned char getObjectAt(int x, int y) const;

		//! @brief Get the object at position pos.
		//! @param pos Position.
		//! @return The object or 00 if out of bound.
		unsigned char getObjectAt(sf::Vector2f pos) const;

		//! @return Returns the player.
		//! @warning Throws if no player or multiple players are found.
		//! @throw CorruptedMapException
		ECS::Entity &getPlayer();

		//! @brief Updates the camera center from the focus point.
		//! @param center Focus point of the camera.
		void updateCameraPosition(sf::Vector2f center);

		//! @brief Sets the borders solid or not.
		//! @param solid New value.
		void setBordersSolid(bool solid);

		//! @brief Resets the object to it's default state.
		void reset();

		//! @brief Updates the entities.
		void update();

		//! @brief Renders the map on a screen.
		void render();

		//! @brief Save the currently loaded map.
		//! @throw MapSavingFailureException
		void saveMap();

		//! @brief Loads the saved map in the saves folder.
		//! @throw MapSavingFailureException
		void loadMap();
	};
}

#endif //THFGAME_MAP_HPP
