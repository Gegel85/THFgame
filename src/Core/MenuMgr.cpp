//
// Created by Gegel85 on 25/09/2019.
//

#include <iostream>
#include "MenuMgr.hpp"
#include "Game.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/InventoryComponent.hpp"

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

	void MenuMgr::_renderInventory(Game &game)
	{
		auto &player = game.state.map.getPlayer();
		auto &inventory = player.getComponent("Inventory").to<ECS::Components::InventoryComponent>();
		auto &screen = *game.resources.screen;
		auto camera = screen.getCameraCenter();
		auto screenSize = screen.getSize();

		game.state.map.render();
		game.state.hud.draw(*game.resources.screen);
		screen.fillColor({120, 120, 120});
		screen.draw({
			static_cast<int>(camera.x - screenSize.x / 2. + 32),
			static_cast<int>(camera.y - screenSize.y / 2. + 32),
			static_cast<int>(screenSize.x) - 64,
			static_cast<int>(screenSize.y) - 64
		});
		screen.textSize(16);
		screen.fillColor();
		for (unsigned i = 0; i < inventory.items.size(); i++) {
			auto &item = inventory.items[i];

			try {
				screen.draw(
					game.resources.textures.at(item->getTexture()),
					{camera.x - screenSize.x / 2.f + 60, camera.y - screenSize.y / 2.f + 40 + i * 32.f}
				);
			} catch (std::out_of_range &) {}
			screen.draw(item->getName(), {camera.x - screenSize.x / 2.f + 90, camera.y - screenSize.y / 2.f + 48 + i * 32.f});
		}
	}

	void MenuMgr::_handleGameEvents(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			case sf::Keyboard::E:
				changeMenu(game, INVENTORY_MENU);
				break;
			case sf::Keyboard::F:
				game.state.map.getPlayer().getComponent("Inventory").to<ECS::Components::InventoryComponent>().addItem(game.resources.items[rand() % game.resources.items.size()]);
				break;
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

	void MenuMgr::_handleInventoryEvents(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
				case sf::Keyboard::E:
					changeMenu(game, IN_GAME_MENU);
					break;
				default:
					break;
			}
		}
	}

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