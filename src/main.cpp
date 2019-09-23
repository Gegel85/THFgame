#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"
#include "Logger.hpp"

namespace Game
{
	Logger logger{"./latest.log", Logger::INFO};
	Game game{
		{
			Screen{"THFgame"}
		},
	};
}

void	game()
{
	while (Game::game.resources.screen.isOpen()) {
		Game::game.resources.screen.clear();
		Game::game.resources.screen.handleEvents();
		Game::game.resources.screen.display();
	}
}

int	main()
{
	Game::logger.info("Starting game.");
	game();
	Game::logger.info("Goodbye !");
	return EXIT_SUCCESS;
}