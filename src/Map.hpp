//
// Created by Gegel85 on 26/09/2019.
//

#ifndef THFGAME_MAP_HPP
#define THFGAME_MAP_HPP


#include <SFML/Audio.hpp>
#include "ECS/Core.hpp"

namespace TouhouFanGame
{
	class Map {
	private:
		unsigned short links[4] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
		sf::Vector2u _size;
		std::string _tileMap;
		std::vector<unsigned char> _objects;
		ECS::Core _core;

	public:
		enum Direction {
			NORTH,
			EAST,
			SOUTH,
			WEST
		};

		Map() = default;
		void serialize(std::ostream &stream);
		void unserialize(std::istream &stream);
		void loadFromFile(const std::string &path);
		void clear();
		void update();
		void render();
	};
}

#endif //THFGAME_MAP_HPP
