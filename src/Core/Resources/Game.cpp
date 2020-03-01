//
// Created by Gegel85 on 12/01/2020.
//

#include "Game.hpp"

namespace TouhouFanGame
{
	Logger logger{"./latest.log", Logger::LOG_DEBUG};

	GameState::GameState(Game &game) :
		map(game),
		hud(game.resources.textures)
	{
	}

	Game::Game() :
		state(*this)
	{
	}
}