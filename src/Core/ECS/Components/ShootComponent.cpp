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
		handler(new DynamicLibrary(handlePath + DLL_EXTENSION)),
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
		stream >> this->_handlerPath;
		this->handler = std::make_unique<DynamicLibrary>(this->_handlerPath + DLL_EXTENSION);
	}

	void ShootComponent::setHandlerPath(const std::string &path)
	{
		this->handler = std::make_unique<DynamicLibrary>(path + DLL_EXTENSION);
		this->_handlerPath = path;
	}

	void ShootComponent::serialize(std::ostream &stream) const
	{
		stream << this->_handlerPath;
	}
}