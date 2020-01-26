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
		//! @brief All the textures
		std::map<std::string, sf::Texture> &_textures;

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

		//! @brief The deck of the player.
		std::vector<std::string> _playerDeck{
			"test_spell_card1",
			"test_spell_card2",
			"test_spell_card3"
		};

		//! @brief The selected player card.
		unsigned _selectedCard = 0;

		//! @brief Renders the player HUD on screen.
		void _renderPlayerHUD(Screen &screen);

		//! @brief Renders the boss HUD on screen.
		void _renderBossHUD(Screen &screen);

		//! @brief Renders the currently playing music's name on screen.
		void _renderMusic(Screen &screen);

		//! @brief Renders the player deck on the screen
		void _renderPlayerDeck(Screen &screen);

		void _renderExpBar(Screen &screen);
		void _renderManaBar(Screen &screen);
		void _renderLifeBar(Screen &screen);

	public:
		HUD(std::map<std::string, sf::Texture> &textures);

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

		//! @brief Set the current exp level of the player.
		//! @param exp The % of exp the player has until level up.
		void setExpLevel(float exp);

		//! @brief Changes the current level of the player.
		//! @param level The new level.
		void setCurrentLevel(unsigned int level);

		//! @brief Changes the player spell card deck.
		//! @param playerDeck An array of texture representing the deck of the player.
		void setPlayerDeck(const std::vector<std::string> &playerDeck);

		//! @brief Change the currently selected player card.
		//! @param selectedCard The new selected card.
		void setSelectedCard(unsigned int selectedCard);

		//! @brief Display the HUD.
		void draw(TouhouFanGame::Game &game);
	};
}


#endif //THFGAME_HUD_HPP
