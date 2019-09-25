//
// Created by Gegel85 on 25/09/2019.
//

#ifndef THFGAME_MENU_HPP
#define THFGAME_MENU_HPP


#include <SFML/Window/Event.hpp>

namespace Game
{
	class MenuMgr {
	private:
		static void _renderMainMenu();
		static void _renderGame();

		static void _handleMainMenuEvents(const sf::Event &);
		static void _handleGameEvents(const sf::Event &);

	public:
		enum Menu {
			MAIN_MENU,
			IN_GAME
		};

		static void renderMenu();
		static void handleEvent(const sf::Event &);
		static void changeMenu(Menu newMenu);
	};
}


#endif //THFGAME_MENU_HPP
