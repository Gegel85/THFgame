//
// Created by Gegel85 on 28/09/2019.
//

#include "DisplayableComponent.hpp"
#include "../../Resources/Game.hpp"

namespace TouhouFanGame::ECS::Components
{
	DisplayableComponent::DisplayableComponent(Resources &resources, std::istream &stream) :
		Component("Displayable"),
		_resources(resources),
		_screen(*resources.screen),
		_configPath([&stream](){
			std::string str;

			stream >> str;
			return str;
		}()),
		renderEntity(resources.screen->addEntity(this->_configPath))
	{
	}

	DisplayableComponent::DisplayableComponent(Resources &resources, const std::string &config) :
		Component("Displayable"),
		_resources(resources),
		_screen(*resources.screen),
		_configPath(config),
		renderEntity(resources.screen->addEntity(config))
	{}

	DisplayableComponent::~DisplayableComponent()
	{
		this->_screen.removeEntity(this->renderEntity);
	}

	void DisplayableComponent::setConfigs(const std::string &path)
	{
		this->_configPath = path;
		this->renderEntity.setConfigs(this->_resources, path);
	}

	void DisplayableComponent::serialize(std::ostream &stream) const
	{
		stream << this->_configPath;
	}
}