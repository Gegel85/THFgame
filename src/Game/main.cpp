#include "../Core/Game.hpp"
#include "../Core/Logger.hpp"
#include "../Core/Loader.hpp"
#include "../Core/Menus/MenuMgr.hpp"
#include "../Core/Exceptions.hpp"
#include "../Core/Utils.hpp"
#include "Menus/MainMenu.hpp"
#include "Menus/InGameMenu.hpp"
#include "Menus/InventoryMenu.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <SFML/Graphics.hpp>
#define ICON_ERROR_PATH "assets/box/error.png"
#endif

namespace TouhouFanGame
{
	//! @brief The global logger
	Logger logger{"./latest.log", Logger::DEBUG};

	void	setup(Game &game)
	{
		logger.debug("Opening main window");
		game.resources.screen.reset(new Rendering::Screen{game.resources, "THFgame"});

		game.state.menuMgr.addMenu<MainMenu>("main_menu", game.state.map, game.resources, game.state.hud);
		game.state.menuMgr.addMenu<InGameMenu>("in_game", game, game.state.map, game.state.hud, *game.resources.screen);
		game.state.menuMgr.addMenu<InventoryMenu>("inventory", game, game.state.map, game.state.hud, *game.resources.screen, game.resources.textures);
	}

	//! @brief The game loop
	void	gameLoop(Game &game)
	{
		sf::Event event;

		game.state.menuMgr.changeMenu("main_menu");
		while (game.resources.screen->isOpen()) {
			game.resources.screen->clear();

			while (game.resources.screen->pollEvent(event))
				if (event.type == sf::Event::Closed)
					game.resources.screen->close();

			for (auto e = game.state.settings.input->pollEvent(); e; e = game.state.settings.input->pollEvent())
				game.state.menuMgr.handleEvent(*e);

			game.state.menuMgr.renderMenu();
			game.resources.screen->display();
		}
	}

	int	run()
	{
		Game game;
		//TODO: Add proper font loading.

		try {
			logger.info("Setting up...");
			setup(game);

			game.resources.font.loadFromFile("assets/arial.ttf");
			game.resources.screen->setFont(game.resources.font);

			logger.info("Loading assets...");
			Loader::loadAssets(game);

			logger.info("Starting game.");
			gameLoop(game);
		} catch (std::exception &e) {
			logger.fatal(getLastExceptionName() + ": " + e.what());
			Utils::dispMsg(
				"Fatal Error",
				"An unrecoverable error occurred\n\n" +
				getLastExceptionName() + ":\n" + e.what() + "\n\n"
				"Click OK to close the application",
				MB_ICONERROR
			);
			return EXIT_FAILURE;
		}
		logger.info("Goodbye !");
		return EXIT_SUCCESS;
	}
}

int	main()
{
	return TouhouFanGame::run();
}
