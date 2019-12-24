//
// Created by Gegel85 on 22/12/2019.
//

#include "../GuiUtils.hpp"
#include "MainMenu.hpp"

namespace TouhouFanGame
{
	MainMenu::MainMenu(MenuMgr &menu, Map &map, tgui::Gui &gui, Rendering::Screen &window) :
		_map(map),
		_menu(menu),
		_gui(gui),
		_window(window)
	{
	}

	void MainMenu::render()
	{
		this->_map.updateCameraPosition({0, 20});
		this->_map.render();
		this->_window.setTitle("THFgame map editor (" + std::to_string(this->_window.getFPS()) + " FPS)");
		this->_gui.draw();
	}

	void MainMenu::switched(bool)
	{
	}

	void MainMenu::handleEvent(const TouhouFanGame::Input::Event &)
	{
	}
}