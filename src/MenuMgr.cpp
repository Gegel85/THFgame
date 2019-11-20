//
// Created by Gegel85 on 25/09/2019.
//

#include <iostream>
#include "MenuMgr.hpp"
#include "Game.hpp"
#include "ECS/Components/PositionComponent.hpp"

namespace TouhouFanGame
{
	void MenuMgr::_renderGame(Game &game)
	{
		game.state.map.update();
		game.state.map.render();
		game.state.hud.draw(*game.resources.screen);
	}

	void MenuMgr::_renderMainMenu(Game &)
	{}

	void MenuMgr::_renderInventory(Game &)
	{}

	void MenuMgr::_handleGameEvents(Game &, const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			default:
				break;
			}
		}
	}

	void MenuMgr::_handleMainMenuEvents(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed)
			changeMenu(game, IN_GAME_MENU);
	}

	void MenuMgr::_handleInventoryEvents(Game &, const sf::Event &)
	{}

	void MenuMgr::handleEvent(Game &game, const sf::Event &event)
	{
		if (event.type == event.Closed)
			game.resources.screen->close();

		switch (game.state.currentMenu) {
		case MAIN_MENU:
			return _handleMainMenuEvents(game, event);
		case IN_GAME_MENU:
			return _handleGameEvents(game, event);
		case INVENTORY_MENU:
			return _handleInventoryEvents(game, event);
		}
	}

	void MenuMgr::renderMenu(Game &game)
	{
		switch (game.state.currentMenu) {
		case MAIN_MENU:
			return _renderMainMenu(game);
		case IN_GAME_MENU:
			return _renderGame(game);
		case INVENTORY_MENU:
			return _renderInventory(game);
		}
	}

	void MenuMgr::changeMenu(Game &game, Menu newMenu)
	{
		switch (newMenu) {
		case MAIN_MENU:
			game.resources.stopMusic();
			game.state.hud.setDispPlayerHUD(false);
			game.state.hud.setDispBossHUD(false);
			game.resources.playMusic("menu");
			break;
		case IN_GAME_MENU:
			game.resources.screen->setCameraCenter({0, 0});
			game.state.hud.setDispPlayerHUD(true);
			game.state.hud.setDispBossHUD(false);
			if (game.state.currentMenu == MAIN_MENU) {
				game.state.map.reset();
				game.state.map.loadMap();
			}
			break;
		case INVENTORY_MENU:
			break;
		}
		game.state.currentMenu = newMenu;
	}
}