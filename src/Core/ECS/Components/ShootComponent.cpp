/*
** EPITECH PROJECT, 2020
** THFgame
** File description:
** ShootComponent.cpp
*/

#include <iostream>
#include "ShootComponent.hpp"
#include "../../ExternalCode/DynamicLibrary.hpp"
#include "../../Resources.hpp"

namespace TouhouFanGame::ECS::Components
{
	ShootComponent::ShootComponent(Resources &resources) :
		Component("Shoot"),
		resources(resources)
	{
	}

	ShootComponent::ShootComponent(Resources &resources, const std::string &handlePath) :
		Component("Shoot"),
		handler(new DynamicLibrary(handlePath + DLL_EXTENSION)),
		resources(resources)
	{
		this->_handlerPath = handlePath;
	}

	ShootComponent::ShootComponent(std::istream &stream, Resources &resources) :
		Component("Shoot"),
		resources(resources)
	{
		std::getline(stream, this->_handlerPath, '\0');
		while (!this->_handlerPath.empty() && std::isspace(this->_handlerPath[0]))
			this->_handlerPath = this->_handlerPath.substr(1);
		this->handler = std::make_unique<DynamicLibrary>(this->_handlerPath + DLL_EXTENSION);
	}

	void ShootComponent::setHandlerPath(const std::string &path)
	{
		this->handler = std::make_unique<DynamicLibrary>(path + DLL_EXTENSION);
		this->_handlerPath = path;
	}

	void ShootComponent::serialize(std::ostream &stream) const
	{
		stream << this->_handlerPath << '\0';
	}
}