//
// Created by Gegel85 on 23/09/2019.
//

#ifndef THFGAME_GAME_HPP
#define THFGAME_GAME_HPP

#include "Rendering/Hud.hpp"
#include "Logger.hpp"
#include "Resources.hpp"
#include "Menus/MenuMgr.hpp"
#include "Map.hpp"
#include "Input/Input.hpp"

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
		MenuMgr menuMgr;

		//! @brief The currently loaded map
		Map map;

		//! @brief The currently displayed HUD.
		Rendering::HUD hud;

		//! @brief Settings of the game
		Settings settings;

		GameState(Game &game);
	};

	//! @brief The game state and resources
	struct Game {
		//! @brief The loaded resources
		Resources resources;

		//! @brief The current game state
		GameState state;

		Game();
	};

	extern Logger logger;
}
#endif //THFGAME_GAME_HPP
