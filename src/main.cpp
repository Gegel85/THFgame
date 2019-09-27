#include <iostream>
#include "Game.hpp"
#include "Logger.hpp"
#include "Loader.hpp"
#include "Menu.hpp"
#include "Exceptions.hpp"

namespace TouhouFanGame
{
	Logger logger{"./latest.log", Logger::DEBUG};
	Game game;

	void	gameLoop()
	{
		sf::Event event;

		MenuMgr::changeMenu(MenuMgr::MAIN_MENU);
		while (game.resources.screen->isOpen()) {
			game.resources.screen->clear();

			while (game.resources.screen->pollEvent(event))
				MenuMgr::handleEvent(event);
			MenuMgr::renderMenu();

			game.resources.screen->display();
		}
	}
}

int	main()
{
	try {
		TouhouFanGame::logger.info("Loading assets...");
		TouhouFanGame::Loader::loadAssets();
		TouhouFanGame::logger.info("Starting game.");
		TouhouFanGame::gameLoop();
		TouhouFanGame::logger.info("Goodbye !");
	} catch (std::exception &e) {
		TouhouFanGame::logger.fatal(getLastExceptionName() + ": " + e.what());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}