//
// Created by Gegel85 on 23/09/2019.
//

#ifndef THFGAME_GAME_HPP
#define THFGAME_GAME_HPP

#include "Logger.hpp"
#include "Resources.hpp"

namespace Game
{
	struct Game {
		Resources resources;
	};

	extern Game game;
	extern Logger logger;
}
#endif //THFGAME_GAME_HPP
