//
// Created by Gegel85 on 26/09/2019.
//

#include "EntityFactory.hpp"
#include "../Exceptions.hpp"
#include "../Components/PositionComponent.hpp"
#include "../Components/DisplayableComponent.hpp"
#include "../Components/MovableComponent.hpp"
#include "../Components/ControllableComponent.hpp"
#include "../Components/BlockedByTerrainComponent.hpp"
#include "../../Game.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/ManaComponent.hpp"
#include "../Components/NameComponent.hpp"
#include "../Components/PlayerHudComponent.hpp"
#include "../Components/InventoryComponent.hpp"

namespace TouhouFanGame::ECS::Factory
{
	const std::map<std::string, std::function<ECS::Entity *(Game &, unsigned int)>> EntityFactory::_builders = {
		{"Player", [](Game &game, unsigned int id){
			return new Entity(id, "Player", {
				new Components::ControllableComponent(*game.state.settings.input, 2, 4),
				new Components::BlockedByTerrainComponent(game.state.map),
				new Components::MovableComponent(),
				new Components::DisplayableComponent(game, "assets/entities/test.json"),
				new Components::PositionComponent({PLAYER_SIZE, PLAYER_SIZE}),
				new Components::HealthComponent(20),
				new Components::ManaComponent(20),
				new Components::NameComponent("Test Character"),
				new Components::PlayerHUDComponent(game.state.hud),
				new Components::InventoryComponent(16)
			}, false);
		}}
	};

	Entity	*EntityFactory::build(Game &game, const std::string &name, unsigned int id)
	{
		try {
			return _builders.at(name)(game, id);
		} catch (std::out_of_range &) {
			throw NoSuchEntityException("Cannot find any way to build a " + name);
		}
	}
}