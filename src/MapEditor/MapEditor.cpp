//
// Created by Gegel85 on 23/12/2019.
//

#include "MapEditor.hpp"
#include "../Core/Loader.hpp"
#include "Menus/MainMenu.hpp"

namespace TouhouFanGame
{
	void MapEditor::setup()
	{
		logger.info("Setting up...");
		logger.debug("Opening main window");
		this->_game.resources.screen = std::make_unique<Rendering::Screen>(this->_game.resources, "THFgame");
		this->_gui = std::make_unique<tgui::Gui>(*this->_game.resources.screen);
		this->_game.state.menuMgr.addMenu<MainMenu>("main_menu", this->_game, *this->_gui, *this->_game.resources.screen);

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
				if (event.type == sf::Event::Closed)
					this->_game.resources.screen->close();
				this->_gui->handleEvent(event);
			}

			for (auto e = this->_game.state.settings.input->pollEvent(); e; e = this->_game.state.settings.input->pollEvent())
				this->_game.state.menuMgr.handleEvent(*e);

			this->_game.state.menuMgr.renderMenu();
			this->_game.resources.screen->display();
		}
		return EXIT_SUCCESS;
	}
}
