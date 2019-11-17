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
	const std::map<std::string, std::function<Component *(Game &, std::istream &)>> ComponentFactory::_builders{
		{"Movable",          [](Game &    , std::istream &stream){ return new Components::MovableComponent(stream); }},
		{"Position",         [](Game &    , std::istream &stream){ return new Components::PositionComponent(stream); }},
		{"Controllable",     [](Game &game, std::istream &stream){ return new Components::ControllableComponent(*game.state.settings.input, stream); }},
		{"Displayable",      [](Game &game, std::istream &stream){ return new Components::DisplayableComponent(game, stream); }},
		{"BlockedByTerrain", [](Game &game, std::istream &      ){ return new Components::BlockedByTerrainComponent(game.state.map); }},
	};

	Component *ComponentFactory::build(Game &game, const std::string &name, std::istream &stream)
	{
		try {
			return _builders.at(name)(game, stream);
		} catch (std::out_of_range &) {
			throw NoSuchComponentException("Cannot find any way to build a " + name + "Component");
		}
	}
}
