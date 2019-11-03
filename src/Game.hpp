//
// Created by Gegel85 on 23/09/2019.
//

#ifndef THFGAME_GAME_HPP
#define THFGAME_GAME_HPP

#include "Logger.hpp"
#include "Resources.hpp"
#include "Menu.hpp"
#include "Map.hpp"
#include "Input.hpp"

namespace TouhouFanGame
{
	//! @brief Describe the current game state
	struct GameState {
		//! @brief The current menu
		MenuMgr::Menu currentMenu;

		//! @brief The currently loaded map
		Map map;

		//! @brief The current music volume
		float musicVolume;

		//! @brief The current sound effect volume
		float sfxVolume;

		//! @brief The current input
		std::unique_ptr<Input> input;
	};

	//! @brief The game state and resources
	struct Game {
		//! @brief The loaded resources
		Resources resources;

		//! @brief The current game state
		GameState state;
	};

	extern Game _game;
	extern Logger logger;
}
#endif //THFGAME_GAME_HPP
