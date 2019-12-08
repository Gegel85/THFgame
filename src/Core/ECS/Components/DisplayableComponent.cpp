//
// Created by Gegel85 on 28/09/2019.
//

#include "DisplayableComponent.hpp"
#include "../../Game.hpp"

namespace TouhouFanGame::ECS::Components
{
	DisplayableComponent::DisplayableComponent(Game &game, std::istream &stream) :
		Component("Displayable"),
		_screen(*game.resources.screen),
		_configPath([&stream](){
			std::string str;

			stream >> str;
			return str;
		}()),
		renderEntity(game.resources.screen->addEntity(this->_configPath))
	{
	}

	DisplayableComponent::DisplayableComponent(Game &game, const std::string &config) :
		Component("Displayable"),
		_screen(*game.resources.screen),
		_configPath(config),
		renderEntity(game.resources.screen->addEntity(config))
	{}

	DisplayableComponent::~DisplayableComponent()
	{
		this->_screen.removeEntity(this->renderEntity);
	}

	void DisplayableComponent::serialize(std::ostream &stream) const
	{
		stream << this->_configPath;
	}
}