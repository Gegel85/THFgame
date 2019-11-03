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

	//! @brief Global game resources and state
	//! @note This is global because some Lua functions needs to access it
	Game _game;

	//! @brief The game loop
	void	gameLoop()
	{
		sf::Event event;

		MenuMgr::changeMenu(_game, MenuMgr::MAIN_MENU);
		while (_game.resources.screen->isOpen()) {
			_game.resources.screen->clear();

			while (_game.resources.screen->pollEvent(event))
				MenuMgr::handleEvent(_game, event);
			MenuMgr::renderMenu(_game);

			_game.resources.screen->display();
		}
	}
}

int	main()
{
	try {
		TouhouFanGame::logger.info("Loading assets...");
		TouhouFanGame::Loader::loadAssets(TouhouFanGame::_game);
		TouhouFanGame::logger.info("Starting game.");
		TouhouFanGame::gameLoop();
		TouhouFanGame::logger.info("Goodbye !");
	} catch (std::exception &e) {
		TouhouFanGame::logger.fatal(getLastExceptionName() + ": " + e.what());
		TouhouFanGame::dispMsg(
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
