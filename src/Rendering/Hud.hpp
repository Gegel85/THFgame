/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** Hud.hpp
*/

#ifndef THFGAME_HUD_HPP
#define THFGAME_HUD_HPP


#include "Screen.hpp"

namespace TouhouFanGame::Rendering
{
	class HUD {
	private:
		float _bossLife = 0;
		float _playerLife = 0;
		float _playerMana = 0;
		unsigned musicNamePos = 0;
		std::string _bossName = "";
		std::string _musicName = "";
		std::string _playerName = "";

	public:
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

		//! @brief Display the HUD on a Screen.
		void draw(Screen &screen);
	};
}


#endif //THFGAME_HUD_HPP
