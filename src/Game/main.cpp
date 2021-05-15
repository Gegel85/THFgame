#include "../Core/Resources/Game.hpp"
#include "../Core/Resources/Logger.hpp"
#include "../Core/Loading/Loader.hpp"
#include "../Core/Menus/MenuMgr.hpp"
#include "../Core/Exceptions.hpp"
#include "../Core/Utils/Utils.hpp"
#include "Menus/MainMenu.hpp"
#include "Menus/InGameMenu.hpp"
#include "Menus/InventoryMenu.hpp"

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#else
#include <unistd.h>
#endif

namespace TouhouFanGame
{
	//! @brief The global logger
	Logger logger{
		"./latest.log",
		#ifdef _DEBUG
		Logger::LOG_DEBUG
		#else
		Logger::LOG_INFO
		#endif
	};

	void	setup(Game &game)
	{
		logger.debug("Opening main window");
		game.resources.screen.reset(new Rendering::Screen{game.resources, "THFgame"});

		game.resources.screen->pushGLStates();
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

	void	run()
	{
		Game game;
		//TODO: Add proper font loading.

		#ifndef _DEBUG
		try {
		#endif

			logger.info("Setting up...");
			setup(game);

			game.resources.font.loadFromFile("assets/arial.ttf");
			game.resources.screen->setFont(game.resources.font);

			logger.info("Loading assets...");
			Loader::loadAssets(game);

			logger.info("Starting game.");
			gameLoop(game);
		#ifndef _DEBUG
		} catch (std::exception &e) {
			logger.fatal(getLastExceptionName() + ": " + e.what());
			Utils::dispMsg(
				"Fatal Error",
				"An unrecoverable error occurred\n\n" +
				getLastExceptionName() + ":\n" + e.what() + "\n\n"
				"Click OK to close the application",
				MB_ICONERROR
			);
			throw;
		}
		#endif
		logger.info("Goodbye !");
	}
}

int	main(int, char **argv)
{
	std::string progPath = argv[0];
	size_t occurence =
#ifdef _WIN32
	progPath.find_last_of('\\');
#else
	progPath.find_last_of('/');
#endif

	if (occurence != std::string::npos)
		chdir(progPath.substr(0, occurence).c_str());
	else
		TouhouFanGame::logger.warn("Cannot find program path from argv (" + progPath + ")");
#ifndef _DEBUG
	try {
#endif
		TouhouFanGame::run();
#ifndef _DEBUG
	} catch (std::exception &) {
		return EXIT_FAILURE;
	}
#endif
	return EXIT_SUCCESS;
}
