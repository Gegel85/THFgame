#include "Core/Game.hpp"
#include "Logger.hpp"
#include "Core/Loader.hpp"
#include "Core/Menus/MenuMgr.hpp"
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
