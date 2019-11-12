//
// Created by Gegel85 on 28/09/2019.
//

#include "DisplayableComponent.hpp"
#include "../../Game.hpp"

namespace TouhouFanGame::ECS::Components
{
	DisplayableComponent::DisplayableComponent(std::istream &stream) :
		Component("Displayable"),
		_configPath([&stream](){
			std::string str;

			stream >> str;
			return str;
		}()),
		renderEntity(_game.resources.screen->addEntity(this->_configPath))
	{
	}

	DisplayableComponent::DisplayableComponent(const std::string &config) :
		Component("Displayable"),
		_configPath(config),
		renderEntity(_game.resources.screen->addEntity(config))
	{}

	DisplayableComponent::~DisplayableComponent()
	{
		_game.resources.screen->removeEntity(this->renderEntity);
	}

	void DisplayableComponent::serialize(std::ostream &stream) const
	{
		stream << this->_configPath;
	}
}