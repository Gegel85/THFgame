//
// Created by Gegel85 on 22/12/2019.
//

#include "MainMenu.hpp"

namespace TouhouFanGame
{
	MainMenu::MainMenu(MenuMgr &menu, Map &map, Resources &resources, Rendering::HUD &hud) :
		_map(map),
		_menu(menu),
		_resources(resources),
		_hud(hud)
	{
	}

	void MainMenu::render()
	{}

	void MainMenu::switched(bool isActive)
	{
		if (isActive) {
			this->_resources.stopMusic();
			this->_resources.playMusic("menu");
		} else {
			this->_map.reset();
			this->_map.loadMap();
		}
	}

	void MainMenu::handleEvent(const TouhouFanGame::Input::Event &event)
	{
		if (event.type == Input::Event::EVENT_TRIGGERED)
			this->_menu.changeMenu("in_game");
	}
}