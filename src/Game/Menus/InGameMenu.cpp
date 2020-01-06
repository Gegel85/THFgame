//
// Created by Gegel85 on 22/12/2019.
//

#include "InGameMenu.hpp"

namespace TouhouFanGame
{
	InGameMenu::InGameMenu(MenuMgr &menu, Game &game, Map &map, Rendering::HUD &hud, Rendering::Screen &screen) :
		_map(map),
		_game(game),
		_menu(menu),
		_hud(hud),
		_screen(screen)
	{
	}

	void InGameMenu::render()
	{
		this->_map.update();
		this->_map.render();
		this->_hud.draw(this->_game);
	}

	void InGameMenu::switched(bool isActive)
	{
		if (!isActive)
			return;

		this->_screen.setCameraCenter({0, 0});
		this->_hud.setDispPlayerHUD(true);
		this->_hud.setDispBossHUD(false);
	}

	void InGameMenu::handleEvent(const Input::Event &event)
	{
		if (event.type == Input::Event::EVENT_TRIGGERED) {
			switch (event.action) {
			case Input::INVENTORY:
				this->_menu.changeMenu("inventory");
				break;
			default:
				break;
			}
		}
	}
}