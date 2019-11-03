//
// Created by Gegel85 on 25/09/2019.
//

#ifndef THFGAME_MENU_HPP
#define THFGAME_MENU_HPP


#include <SFML/Window/Event.hpp>

namespace TouhouFanGame
{
	struct Game;

	//! @brief Manages the menus
	class MenuMgr {
	private:
		static void _renderMainMenu(Game &game);
		static void _renderGame(Game &game);

		static void _handleMainMenuEvents(Game &game, const sf::Event &);
		static void _handleGameEvents(Game &game, const sf::Event &);

	public:
		//! @brief All the menus
		enum Menu {
			MAIN_MENU,
			IN_GAME
		};

		//! @brief Renders the current Menu on the screen
		//! @param game Game resources
		static void renderMenu(Game &game);

		//! @brief Consumes an sf::Event
		//! @param game Game resources
		static void handleEvent(Game &game, const sf::Event &);

		//! @brief Changes the current Menu
		//! @param game Game resources
		//! @param newMenu The new menu
		static void changeMenu(Game &game, Menu newMenu);
	};
}


#endif //THFGAME_MENU_HPP
