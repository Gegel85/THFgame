//
// Created by Gegel85 on 23/09/2019.
//

#ifndef THFGAME_GAME_HPP
#define THFGAME_GAME_HPP

#include "../Rendering/Hud.hpp"
#include "Logger.hpp"
#include "Resources.hpp"
#include "../Menus/MenuMgr.hpp"
#include "Map.hpp"
#include "../Input/Input.hpp"

namespace TouhouFanGame
{
	//! @brief Describes the settings of the game.
	struct Settings : public BaseObject {
		//! @brief The current music volume
		float musicVolume;

		//! @brief The current sound effect volume
		float sfxVolume;

		//! @brief The current input
		std::unique_ptr<Input> input;
		~Settings() override = default;
	};

	//! @brief Describe the current game state
	struct GameState : public BaseObject {
		//! @brief The current menu
		MenuMgr menuMgr;

		//! @brief The currently loaded map
		Map map;

		//! @brief The currently displayed HUD.
		Rendering::HUD hud;

		//! @brief Settings of the game
		Settings settings;

		GameState(Game &game);
		~GameState() override = default;
	};

	//! @brief The game state and resources
	struct Game : public BaseObject {
		//! @brief The loaded resources
		Resources resources;

		//! @brief The current game state
		GameState state;

		Game();
		~Game() override = default;
	};

	extern Logger logger;
}
#endif //THFGAME_GAME_HPP
