#include "Game.hpp"
#include "Logger.hpp"
#include "Loader.hpp"
#include "Menu.hpp"
#include "Exceptions.hpp"
#include "Utils.hpp"

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

	//! @brief The game loop
	void	gameLoop(Game &game)
	{
		sf::Event event;

		MenuMgr::changeMenu(game, MenuMgr::MAIN_MENU);
		while (game.resources.screen->isOpen()) {
			game.resources.screen->clear();

			while (game.resources.screen->pollEvent(event))
				MenuMgr::handleEvent(game, event);
			MenuMgr::renderMenu(game);

			game.resources.screen->display();
		}
	}
}

int	main()
{
	TouhouFanGame::Game game;
	//TODO: Add proper font loading.
	sf::Font font;

	font.loadFromFile("assets/arial.ttf");

	try {
		TouhouFanGame::logger.info("Loading assets...");
		TouhouFanGame::Loader::loadAssets(game);
		game.resources.screen->setFont(font);
		TouhouFanGame::logger.info("Starting game.");
		TouhouFanGame::gameLoop(game);
		TouhouFanGame::logger.info("Goodbye !");
	} catch (std::exception &e) {
		TouhouFanGame::logger.fatal(getLastExceptionName() + ": " + e.what());
		TouhouFanGame::Utils::dispMsg(
			"Fatal Error",
			"An unrecoverable error occurred\n\n" +
			getLastExceptionName() + ":\n" + e.what() + "\n\n"
			"Click OK to close the application",
			MB_ICONERROR
		);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
