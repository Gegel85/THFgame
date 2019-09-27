//
// Created by Gegel85 on 23/09/2019.
//

#ifndef THFGAME_GAME_HPP
#define THFGAME_GAME_HPP

#include "Logger.hpp"
#include "Resources.hpp"
#include "Menu.hpp"
#include "Map.hpp"

namespace TouhouFanGame
{
	struct GameState {
		MenuMgr::Menu currentMenu;
		Map map;
	};

	struct Game {
		Resources resources;
		GameState state;
	};

	extern Game game;
	extern Logger logger;
}
#endif //THFGAME_GAME_HPP
