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
		unsigned short _links[4] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
		sf::Vector2<unsigned char> _size;
		unsigned char _tileSize;
		std::string _tileMap;
		std::vector<unsigned char> _objects;
		std::map<sf::Vector2f, std::pair<unsigned short, sf::Vector2u>> _tpTriggers;
		ECS::Core _core;
		sf::Vector2f _cameraCenter;

		static float _updateCameraCenter(float size, float screenSize, float focusPoint);
		sf::Vector2f &_getPlayerPosition();
		sf::Vector2u &_getPlayerSize();
		ECS::Entity &_getPlayer();
	public:

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
