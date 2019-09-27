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
		bool _cameraUpdated = false;
		unsigned short links[4] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
		sf::Vector2u _size;
		unsigned _tileSize;
		std::string _tileMap;
		std::vector<unsigned char> _objects;
		std::map<sf::Vector2u, std::pair<unsigned short, sf::Vector2u>> _tpTriggers;
		ECS::Core _core;
		sf::Vector2f _cameraCenter;

		float _updateCameraCenter(float size, float screenSize, float focusPoint);
		sf::Vector2f _getPlayerPosition();
	public:
		ECS::Entity &_getPlayer();

		Map() = default;
		void serialize(std::ostream &stream);
		void unserialize(std::istream &stream);
		void loadFromFile(const std::string &path);
		void updateCameraPosition(sf::Vector2f center);
		void clear();
		void update();
		void render();
	};
}

#endif //THFGAME_MAP_HPP
