//
// Created by Gegel85 on 28/09/2019.
//

#include "DisplayableComponent.hpp"
#include "../../Game.hpp"

namespace TouhouFanGame::ECS::Components
{
	DisplayableComponent::DisplayableComponent(const std::string &config) :
		Component("Displayable"),
		_configPath(config),
		renderEntity(_game.resources.screen->addEntity(config))
	{}

	DisplayableComponent::~DisplayableComponent()
	{
		_game.resources.screen->removeEntity(this->renderEntity);
	}

	void DisplayableComponent::serialize(std::ostream &) const
	{}

	void DisplayableComponent::unserialize(std::istream &)
	{}
}