//
// Created by Gegel85 on 25/09/2019.
//

#include <iostream>
#include "Menu.hpp"
#include "Game.hpp"

namespace Game
{
	void MenuMgr::_renderGame()
	{}

	void MenuMgr::_renderMainMenu()
	{}

	void MenuMgr::_handleGameEvents(const sf::Event &)
	{}

	void MenuMgr::_handleMainMenuEvents(const sf::Event &)
	{}

	void MenuMgr::handleEvent(const sf::Event &event)
	{
		if (event.type == event.Closed)
			game.resources.screen->close();

		switch (game.state.currentMenu) {
		case MAIN_MENU:
			_handleMainMenuEvents(event);
			break;
		case IN_GAME:
			_handleGameEvents(event);
			break;
		}
	}

	void MenuMgr::renderMenu()
	{
		switch (game.state.currentMenu) {
		case MAIN_MENU:
			_renderMainMenu();
			break;
		case IN_GAME:
			_renderGame();
			break;
		}
	}

	void MenuMgr::changeMenu(Menu newMenu)
	{
		game.state.currentMenu = newMenu;
		switch (newMenu) {
		case MAIN_MENU:
			game.resources.musics.at("menu").play();
			break;
		case IN_GAME:
			game.resources.musics.at("menu").stop();
			break;
		}
	}
}