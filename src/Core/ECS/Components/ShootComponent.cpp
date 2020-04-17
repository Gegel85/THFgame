/*
** EPITECH PROJECT, 2020
** THFgame
** File description:
** ShootComponent.cpp
*/

#include <iostream>
#include "ShootComponent.hpp"
#include "../../ExternalCode/DynamicLibrary.hpp"
#include "../../Resources/Resources.hpp"
#include "../../ExternalCode/ExternalModuleFactory.hpp"
#include "../Exceptions.hpp"

namespace TouhouFanGame::ECS::Components
{
	ShootComponent::ShootComponent(Resources &resources, Map &map) :
		Component("Shoot"),
		map(map),
		resources(resources)
	{
	}

	ShootComponent::ShootComponent(Resources &resources, Map &map, const std::string &handlePath) :
		Component("Shoot"),
		handler(ExternalModuleFactory::build(handlePath)),
		map(map),
		resources(resources)
	{
		this->_handlerPath = handlePath;
	}

	ShootComponent::ShootComponent(std::istream &stream, Map &map, Resources &resources) :
		Component("Shoot"),
		map(map),
		resources(resources)
	{
		stream >> this->startCooldown >> this->_handlerPath;
		if (stream.fail())
			throw InvalidSerializedString("Invalid ShootComponent");
		this->handler.reset(ExternalModuleFactory::build(this->_handlerPath));
	}

	void ShootComponent::setHandlerPath(const std::string &path)
	{
		this->handler.reset(ExternalModuleFactory::build(path));
		this->_handlerPath = path;
	}

	void ShootComponent::serialize(std::ostream &stream) const
	{
		stream << this->startCooldown << " " << this->_handlerPath;
	}

	std::string ShootComponent::getHandlerPath() const
	{
		return this->_handlerPath;
	}
}