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
	//! @brief Serialize an SFML Vector2 of 2 numbers.
	//! @details It will serialize the vector in a string like this "({x_value}, {y_value})".
	//! @param vec The vector to serialize.
	//! @return The serialized string.
	template<typename type>
	std::string toString(sf::Vector2<type> &vec)
	{
		return "(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ")";
	}

	//! @brief Display a Windows dialog box.
	//! @details This functions opens a Windows dialog box and return the button clicked by the user.
	//! @param title The title of the window.
	//! @param content The content of the box.
	//! @param variate A bit combination of the window attributes (see Windows MessageBox function for a list of the enums).
	//! @return The button clicked by the user.
	//! @note On Non-Windows systems, it will simulate the Windows dialog box. Only only MB_YESNO, MB_ICONERROR and MB_OK are simulated on those systems.
	int	dispMsg(const std::string &title, const std::string &content, int variate);
}

#endif //THFGAME_UTILS_HPP
