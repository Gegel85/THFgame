/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** ComponentFactory.cpp
*/

#include "ComponentFactory.hpp"
#include "../Components/PositionComponent.hpp"
#include "../Exceptions.hpp"

namespace TouhouFanGame::ECS::Factory
{
	const std::map<std::string, std::function<Component *()>> ComponentFactory::_builders{
		{"Position", [](){ return new Components::PositionComponent({0, 0}); }}
	};

	Component *ComponentFactory::build(const std::string &name)
	{
		try {
			return _builders.at(name)();
		} catch (std::out_of_range &) {
			throw NoSuchComponentException("Cannot find any way to build a " + name + "Component");
		}
	}
}
