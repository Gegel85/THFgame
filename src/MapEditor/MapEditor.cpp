//
// Created by Gegel85 on 23/12/2019.
//

#include <TGUI/TGUI.hpp>
#include "MapEditor.hpp"
#include "../Core/Loader.hpp"
#include "Menus/MainMenu.hpp"
#include "GuiUtils.hpp"

namespace TouhouFanGame
{
	MapEditor::MapEditor() :
		_map(this->_game)
	{
	}

	void MapEditor::_displaySettings()
	{
		auto win = openWindowWithFocus(*this->_gui);

		win->setTitle("Settings");
		win->setSize(400, 400);
		win->loadWidgetsFromFile("assets/gui/Settings.txt");
		win->setFocused(true);

		auto slider = win->get<tgui::Slider>("VolumeSlider");

		slider->setMinimum(0);
		slider->setMaximum(100);
		slider->setValue(this->_game.state.settings.musicVolume);
		slider->connect("ValueChanged", [this, slider]() {
			this->_game.state.settings.musicVolume = slider->getValue();
			this->_game.resources.setMusicVolume(this->_game.state.settings.musicVolume);
		});
	}

	void MapEditor::_makeAllWidgets()
	{
		this->_gui->loadWidgetsFromFile("assets/gui/MapEditor.txt");

		auto menuBar = this->_gui->get<tgui::MenuBar>("main_bar");
		menuBar->connect("MouseEntered", [](tgui::Widget::Ptr bar, const std::string&){
			bar->moveToFront();
		});
		menuBar->connectMenuItem({"File", "Load map"}, [this, menuBar]{
			showLoadFileWindow(*this->_gui, "Load map", "Open", 0, [this, menuBar](unsigned short id) {
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
			showLoadFileWindow(*this->_gui, "Save map", "Save", 0, [this](unsigned short id) {
				this->_map.saveMapToFile("assets/maps/map_" + std::to_string(id) + ".map");
			});
		});
		menuBar->connectMenuItem({"File", "Settings"}, [this]{
			this->_displaySettings();
		});
		menuBar->connectMenuItem({"File", "Quit"}, [this]{
			this->_game.resources.screen->close();
		});
	}

	void MapEditor::_renderMap()
	{
		this->_map.updateCameraPosition({0, 20});
		this->_map.render();
	}

	void MapEditor::setup()
	{
		logger.info("Setting up...");
		logger.debug("Opening main window");
		this->_game.resources.screen = std::make_unique<Rendering::Screen>(this->_game.resources, "THFgame map editor", 800, 640);
		this->_gui = std::make_unique<tgui::Gui>(*this->_game.resources.screen);
		this->_game.state.menuMgr.addMenu<MainMenu>("main_menu", this->_map, *this->_gui, *this->_game.resources.screen);

		this->_makeAllWidgets();
		this->_font.loadFromFile("assets/arial.ttf");
		this->_game.resources.screen->setFont(this->_font);

		logger.info("Loading assets...");
		Loader::loadAssets(this->_game);
	}

	int MapEditor::run()
	{
		if (!this->_game.resources.screen)
			return EXIT_FAILURE;

		sf::Event event;

		logger.info("Starting editor.");
		this->_game.state.menuMgr.changeMenu("main_menu");
		while (this->_game.resources.screen->isOpen()) {
			this->_game.resources.screen->clear();

			while (this->_game.resources.screen->pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					this->_game.resources.screen->close();
					break;
				case sf::Event::Resized:
					this->_game.resources.screen->setView(sf::View{sf::FloatRect(0, 0, event.size.width, event.size.height)});
					this->_gui->setView(sf::View{sf::FloatRect(0, 0, event.size.width, event.size.height)});
					break;
				default:
					break;
				}
				this->_gui->handleEvent(event);
			}

			for (auto e = this->_game.state.settings.input->pollEvent(); e; e = this->_game.state.settings.input->pollEvent())
				this->_game.state.menuMgr.handleEvent(*e);

			this->_renderMap();
			this->_game.state.menuMgr.renderMenu();
			this->_game.resources.screen->display();
		}
		return EXIT_SUCCESS;
	}
}
