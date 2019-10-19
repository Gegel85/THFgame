//
// Created by Gegel85 on 26/09/2019.
//

#ifndef THFGAME_MAP_HPP
#define THFGAME_MAP_HPP


#include <SFML/Audio.hpp>
#include "ECS/Core.hpp"

#define PLAYER_SIZE 32

namespace TouhouFanGame
{
	class Map {
	private:
		struct TpTrigger {
			sf::Vector2<unsigned short> location;
			unsigned short mapId;
			sf::Vector2<unsigned short> mapSpawn;

			TpTrigger(std::istream &stream);
		};

		bool _cameraUpdated = false;
		unsigned short _links[4] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
		sf::Vector2<unsigned short> _size;
		unsigned char _tileSize;
		std::string _tileMap;
		std::vector<unsigned char> _objects;
		std::vector<TpTrigger> _tpTriggers;
		ECS::Core _core;
		sf::Vector2f _cameraCenter;

		template<typename type>
		static type _readInteger(std::istream &stream) {
			char byte;
			type result = 0;

			for (size_t i = 0; i < sizeof(result); i++) {
				stream.read(&byte, 1);
				result = result << 8U | byte;
			}
			return result;
		}
		static float _updateCameraCenter(float size, float screenSize, float focusPoint);
		sf::Vector2f &_getPlayerPosition();
		sf::Vector2u &_getPlayerSize();
		ECS::Entity &_getPlayer();

	public:
		Map() = default;
		unsigned char getTileSize() const;
		unsigned char getObjectAt(int x, int y) const;
		unsigned char getObjectAt(sf::Vector2f pos) const;
		void serialize(std::ostream &stream) const;
		void unserialize(std::istream &stream);
		void loadFromFile(const std::string &path, bool loadEntities = true);
		void loadFromStream(std::istream &stream, bool loadEntities = true);
		void updateCameraPosition(sf::Vector2f center);
		void reset();
		void update();
		void render();
	};
}

#endif //THFGAME_MAP_HPP
