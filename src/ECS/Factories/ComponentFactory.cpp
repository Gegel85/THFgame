/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** ComponentFactory.cpp
*/

#include "../../Game.hpp"
#include "ComponentFactory.hpp"
#include "../Components/PositionComponent.hpp"
#include "../Exceptions.hpp"
#include "../Components/ControllableComponent.hpp"
#include "../Components/MovableComponent.hpp"
#include "../Components/DisplayableComponent.hpp"
#include "../Components/BlockedByTerrainComponent.hpp"

namespace TouhouFanGame::ECS::Factory
{
	const std::map<std::string, std::function<Component *(std::istream &)>> ComponentFactory::_builders{
		{"Movable",          [](std::istream &stream){ return new Components::MovableComponent(stream); }},
		{"Position",         [](std::istream &stream){ return new Components::PositionComponent(stream); }},
		{"Controllable",     [](std::istream &stream){ return new Components::ControllableComponent(*_game.state.input, stream); }},
		{"Displayable",      [](std::istream &stream){ return new Components::DisplayableComponent(stream); }},
		{"BlockedByTerrain", [](std::istream &      ){ return new Components::BlockedByTerrainComponent(_game.state.map); }},
	};

	Component *ComponentFactory::build(const std::string &name, std::istream &stream)
	{
		try {
			return _builders.at(name)(stream);
		} catch (std::out_of_range &) {
			throw NoSuchComponentException("Cannot find any way to build a " + name + "Component");
		}
	}
}
