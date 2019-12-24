//
// Created by Gegel85 on 22/12/2019.
//

#include "../GuiUtils.hpp"
#include "MainMenu.hpp"

namespace TouhouFanGame
{
	MainMenu::MainMenu(MenuMgr &menu, Game &game, tgui::Gui &gui, sf::RenderWindow &window) :
		_map(game),
		_menu(menu),
		_gui(gui),
		_window(window)
	{
	}

	void MainMenu::_addAllWidgets()
	{
		this->_gui.loadWidgetsFromFile("assets/gui/MapEditor.txt");

		auto menuBar = this->_gui.get<tgui::MenuBar>("main_bar");
		menuBar->connect("MouseEntered", [](tgui::Widget::Ptr bar, const std::string&){
			bar->moveToFront();
		});
		menuBar->connectMenuItem({"File", "Load map"}, [this, menuBar]{
			showLoadFileWindow(this->_gui, "Load map", "Open", 0, [this, menuBar](unsigned short id) {
				this->_map.loadFromFile("assets/maps/map_" + std::to_string(id) + ".map");
				this->_loaded = id;
				menuBar->setMenuItemEnabled({"File", "Save"}, true);
				menuBar->setMenuItemEnabled({"File", "Save as"}, true);
			});
		});
		menuBar->connectMenuItem({"File", "Save"}, [this]{
			this->_map.saveMapToFile("assets/maps/map_" + std::to_string(this->_loaded) + ".map");
		});
		menuBar->connectMenuItem({"File", "Save as"}, [this]{
			showLoadFileWindow(this->_gui, "Load map", "Open", 0, [this](unsigned short id) {
				this->_map.saveMapToFile("assets/maps/map_" + std::to_string(id) + ".map");
			});
		});
		menuBar->connectMenuItem({"File", "Quit"}, [this]{
			this->_window.close();
		});
	}

	void MainMenu::render()
	{
		this->_gui.draw();
	}

	void MainMenu::switched(bool isActive)
	{
		if (isActive)
			this->_addAllWidgets();
		else
			this->_gui.removeAllWidgets();
	}

	void MainMenu::handleEvent(const TouhouFanGame::Input::Event &)
	{
	}
}