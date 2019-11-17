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
	//! @brief Describes the settings of the game.
	struct Settings {
		//! @brief The current music volume
		float musicVolume;

		//! @brief The current sound effect volume
		float sfxVolume;

		//! @brief The current input
		std::unique_ptr<Input> input;
	};

	//! @brief Describe the current game state
	struct GameState {
		//! @brief The current menu
		MenuMgr::Menu currentMenu;

		//! @brief The currently loaded map
		Map map;

		//! @brief Settings of the game
		Settings settings;

		GameState(Game &game) : map(game) {};
	};

	//! @brief The game state and resources
	struct Game {
		//! @brief The loaded resources
		Resources resources;

		//! @brief The current game state
		GameState state;

		Game() : state(*this) {};
	};

	extern Logger logger;
}
#endif //THFGAME_GAME_HPP
