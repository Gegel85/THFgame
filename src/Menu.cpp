//
// Created by Gegel85 on 25/09/2019.
//

#include <iostream>
#include "Menu.hpp"
#include "Game.hpp"
#include "ECS/Components/PositionComponent.hpp"

namespace TouhouFanGame
{
	void MenuMgr::_renderGame()
	{
		game.state.map.update();
		game.state.map.render();
	}

	void MenuMgr::_renderMainMenu()
	{}

	void MenuMgr::_handleGameEvents(const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			default:
				break;
			}
		}
	}

	void MenuMgr::_handleMainMenuEvents(const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed)
			changeMenu(IN_GAME);
	}

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
		game.resources.screen->setCamera({0, 0});
		game.resources.stopMusic();
		game.state.currentMenu = newMenu;
		switch (newMenu) {
		case MAIN_MENU:
			game.resources.playMusic("menu");
			break;
		case IN_GAME:
			game.state.map.reset();
			game.state.map.loadFromFile("assets/maps/map_0.map");
			game.resources.musics.at("menu").stop();
			break;
		}
	}
}