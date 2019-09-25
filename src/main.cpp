#ifdef __GNUG__
#include <cxxabi.h>
#endif
#include <iostream>
#include "Game.hpp"
#include "Logger.hpp"
#include "Loader.hpp"
#include "Menu.hpp"

std::string getLastExceptionName()
{
#ifdef __GNUG__
	int status;
	char *value;
	std::string name;

	if (!abi::__cxa_current_exception_type())
		return "No exception";
	auto val = abi::__cxa_current_exception_type();

	if (!val)
		return "No exception";
	value = abi::__cxa_demangle(val->name(), nullptr, nullptr, &status);
	name = value;
	free(value);
	return name;
#else
	return "Unknown exception";
#endif
}


namespace Game
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
		Game::logger.info("Loading assets...");
		Game::Loader::loadAssets();
		Game::logger.info("Starting game.");
		Game::gameLoop();
		Game::logger.info("Goodbye !");
	} catch (std::exception &e) {
		Game::logger.fatal(getLastExceptionName() + ": " + e.what());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}