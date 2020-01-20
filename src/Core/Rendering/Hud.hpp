/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** Hud.hpp
*/

#ifndef THFGAME_HUD_HPP
#define THFGAME_HUD_HPP


#include "Screen.hpp"
#include "../Dialogs/DialogMgr.hpp"

#define HUD_VERTICAL_SIZE 54
#define HUD_HORIZONTAL_SIZE 0

namespace TouhouFanGame::Rendering
{
	class HUD {
	private:
		//! @brief Whether the boss HUD should be displayed.
		bool _dispBoss = false;

		//! @brief Whether the player HUD should be displayed.
		bool _dispPlayer = false;

		//! @brief The current boss life %.
		float _bossLife = 0;

		//! @brief The current player life %.
		float _playerLife = 0;

		//! @brief The current player EXP %.
		float _exp = 0;

		//! @brief The current player level.
		unsigned _level = 0;

		//! @brief The current player mana %.
		float _playerMana = 0;

		//! @brief Internal counter for the music.
		unsigned _musicNamePos = 0;

		//! @brief The current boss name.
		std::string _bossName = "";

		//! @brief The current music name.
		std::string _musicName = "";

		//! @brief The current player name.
		std::string _playerName = "";

		//! @brief The dialog curently on screen
		DialogMgr *_dialog = nullptr;

		//! @brief Renders the player HUD on screen.
		void _renderPlayerHUD(Screen &screen);

		//! @brief Renders the boss HUD on screen.
		void _renderBossHUD(Screen &screen);

		//! @brief Renders the currently playing music's name on screen.
		void _renderMusic(Screen &screen);

	public:
		void setDispBossHUD(bool dispBoss);

		void setDispPlayerHUD(bool dispPlayer);

		//! @brief Set music name.
		//! @param musicName New name.
		void setMusicName(const std::string &musicName);

		//! @brief Set the boss life.
		//! @param bossLife The life percent the boss has.
		void setBossLife(float bossLife);

		//! @brief Set the boss life.
		//! @param playerLife The life percent the player has.
		void setPlayerLife(float playerLife);

		//! @brief Set the boss life.
		//! @param playerMana The mana percent the player has.
		void setPlayerMana(float playerMana);

		//! @brief Set the boss life.
		//! @param bossName The name the boss has.
		void setBossName(const std::string &bossName);

		//! @brief Set the boss life.
		//! @param playerName The name the player has.
		void setPlayerName(const std::string &playerName);

		//! @brief Changes the dialog currently displayed.
		void setDialogManager(DialogMgr *manager);

		void setExpLevel(float exp);

		void setCurrentLevel(unsigned int level);

		//! @brief Display the HUD.
		void draw(TouhouFanGame::Game &game);
	};
}


#endif //THFGAME_HUD_HPP
