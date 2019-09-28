//
// Created by Gegel85 on 26/09/2019.
//

#include "EntityFactory.hpp"
#include "../Exceptions.hpp"
#include "../Components/PositionComponent.hpp"
#include "../Components/DisplayableComponent.hpp"
#include "../Components/MovableComponent.hpp"
#include "../Components/ControllableComponent.hpp"
#include "../../Map.hpp"
#include "../../Game.hpp"

namespace TouhouFanGame::ECS::Factory
{
	const std::map<std::string, std::function<ECS::Entity *(unsigned int)>> EntityFactory::_builders = {
		{"Player", [](unsigned int id){
			return new Entity(id, "Player", {
				new Components::PositionComponent({PLAYER_SIZE, PLAYER_SIZE}),
				new Components::ControllableComponent(*game.state.input, 2, 4),
				new Components::MovableComponent(),
				new Components::DisplayableComponent("assets/entities/test.json")
			});
		}}
	};

	Entity	*EntityFactory::build(const std::string &name, unsigned int id)
	{
		try {
			return _builders.at(name)(id);
		} catch (std::out_of_range &) {
			throw NoSuchEntityException("Cannot find any way to build a " + name);
		}
	}
}