//
// Created by Gegel85 on 23/09/2019.
//

#ifndef THFGAME_GAME_HPP
#define THFGAME_GAME_HPP

#include "Logger.hpp"
#include "Resources.hpp"
#include "Menu.hpp"

namespace Game
{
	struct GameState {
		MenuMgr::Menu currentMenu;
	};

	struct Game {
		Resources resources;
		GameState state;
	};

	extern Game game;
	extern Logger logger;
}
#endif //THFGAME_GAME_HPP
