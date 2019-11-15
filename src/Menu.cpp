//
// Created by Gegel85 on 25/09/2019.
//

#include <iostream>
#include "Menu.hpp"
#include "Game.hpp"
#include "ECS/Components/PositionComponent.hpp"

namespace TouhouFanGame
{
	void MenuMgr::_renderGame(Game &game)
	{
		game.state.map.update();
		game.state.map.render();
	}

	void MenuMgr::_renderMainMenu(Game &)
	{}

	void MenuMgr::_handleGameEvents(Game &, const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			case sf::Keyboard::F:
				_game.state.map.saveMap();
			default:
				break;
			}
		}
	}

	void MenuMgr::_handleMainMenuEvents(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed)
			changeMenu(game, IN_GAME);
	}

	void MenuMgr::handleEvent(Game &game, const sf::Event &event)
	{
		if (event.type == event.Closed)
			game.resources.screen->close();

		switch (game.state.currentMenu) {
		case MAIN_MENU:
			_handleMainMenuEvents(game, event);
			break;
		case IN_GAME:
			_handleGameEvents(game, event);
			break;
		}
	}

	void MenuMgr::renderMenu(Game &game)
	{
		switch (game.state.currentMenu) {
		case MAIN_MENU:
			_renderMainMenu(game);
			break;
		case IN_GAME:
			_renderGame(game);
			break;
		}
	}

	void MenuMgr::changeMenu(Game &game, Menu newMenu)
	{
		game.resources.screen->setCamera({0, 0});
		game.resources.stopMusic();
		game.state.currentMenu = newMenu;
		switch (newMenu) {
		case MAIN_MENU:
			game.resources.playMusic("menu");
			break;
		case IN_GAME:
			game.state.map.reset();
			game.state.map.loadMap();
			break;
		}
	}
}