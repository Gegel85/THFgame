//
// Created by Gegel85 on 19/10/2019.
//

#ifndef THFGAME_UTILS_HPP
#define THFGAME_UTILS_HPP

#include <SFML/System/Vector2.hpp>
#include <string>

#ifndef _WIN32
#define MB_ICONERROR 1
#define MB_YESNO 2
#else
#include <windows.h>
#endif

namespace TouhouFanGame
{
	template<typename type>
	std::string toString(sf::Vector2<type> &vec)
	{
		return "(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ")";
	}

	int	dispMsg(const std::string &title, const std::string &content, int variate);
}

#endif //THFGAME_UTILS_HPP
