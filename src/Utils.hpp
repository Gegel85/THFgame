//
// Created by Gegel85 on 19/10/2019.
//

#ifndef THFGAME_UTILS_HPP
#define THFGAME_UTILS_HPP

#include <SFML/System/Vector2.hpp>
#include <string>

namespace TouhouFanGame
{
	template<typename type>
	std::string toString(sf::Vector2<type> &vec)
	{
		return "(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ")";
	}
}

#endif //THFGAME_UTILS_HPP
