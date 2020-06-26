/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** ComponentFactory.cpp
*/

#include "../Quadtree/RectangleCollider.hpp"
#include "../../Resources/Game.hpp"
#include "ComponentFactory.hpp"
#include "../Components/PositionComponent.hpp"
#include "../Exceptions.hpp"
#include "../Components/ControllableComponent.hpp"
#include "../Components/MovableComponent.hpp"
#include "../Components/DisplayableComponent.hpp"
#include "../Components/BlockedByTerrainComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/ManaComponent.hpp"
#include "../Components/NameComponent.hpp"
#include "../Components/PlayerHudComponent.hpp"
#include "../Components/InventoryComponent.hpp"
#include "../Components/InteractComponent.hpp"
#include "../Components/CollisionComponent.hpp"
#include "../Components/ColliderComponent.hpp"
#include "../Components/DialogComponent.hpp"
#include "../Components/ShootComponent.hpp"
#include "../Components/OobDieComponent.hpp"
#include "../Components/ExperienceComponent.hpp"
#include "../Components/DeckComponent.hpp"
#include "../Components/AiComponent.hpp"
#include "../Components/CutsceneComponent.hpp"
#include "../Components/BossHudComponent.hpp"
#include "../Components/ProjectileComponent.hpp"

namespace TouhouFanGame::ECS::Factory
{
	const std::map<std::string, std::function<Component *(Game &, std::istream &)>> ComponentFactory::_builders{
		{"Movable",          [](Game &    , std::istream &stream){ return new Components::MovableComponent(stream); }},
		{"Position",         [](Game &    , std::istream &stream){ return new Components::PositionComponent(stream); }},
		{"Controllable",     [](Game &game, std::istream &stream){ return new Components::ControllableComponent(*game.state.settings.input, stream); }},
		{"Displayable",      [](Game &game, std::istream &stream){ return new Components::DisplayableComponent(game.resources, stream); }},
		{"BlockedByTerrain", [](Game &game, std::istream &      ){ return new Components::BlockedByTerrainComponent(game.state.map); }},
		{"Mana",             [](Game &    , std::istream &stream){ return new Components::ManaComponent(stream); }},
		{"Health",           [](Game &    , std::istream &stream){ return new Components::HealthComponent(stream); }},
		{"Name",             [](Game &    , std::istream &stream){ return new Components::NameComponent(stream); }},
		{"PlayerHUD",        [](Game &game, std::istream &      ){ return new Components::PlayerHUDComponent(game.state.hud); }},
		{"Inventory",        [](Game &game, std::istream &stream){ return new Components::InventoryComponent(stream, game.resources.items); }},
		{"Interact",         [](Game &    , std::istream &      ){ return new Components::InteractComponent(); }},
		{"Collision",        [](Game &    , std::istream &stream){ return new Components::CollisionComponent(stream); }},
		{"Collider",         [](Game &    , std::istream &stream){ return new Components::ColliderComponent(stream); }},
		{"Dialog",           [](Game &    , std::istream &stream){ return new Components::DialogComponent(stream); }},
		{"Experience",       [](Game &    , std::istream &stream){ return new Components::ExperienceComponent(stream); }},
		{"Deck",             [](Game &    , std::istream &stream){ return new Components::DeckComponent(stream); }},
		{"Shoot",            [](Game &game, std::istream &stream){ return new Components::ShootComponent(stream, game); }},
		{"OOBDie",           [](Game &game, std::istream &      ){ return new Components::OOBDieComponent(game.state.map); }},
		{"AI",               [](Game &game, std::istream &stream){ return new Components::AIComponent(stream, game.state.map, game.state.map.getECSCore()); }},
		{"Cutscene",         [](Game &game, std::istream &stream){ return new Components::CutsceneComponent(game, stream); }},
		{"BossHUD",          [](Game &game, std::istream &      ){ return new Components::BossHUDComponent(game.state.hud); }},
		{"Projectile",       [](Game &game, std::istream &stream){ return new Components::ProjectileComponent(game, stream); }}
	};
	const std::map<std::string, std::function<Component *(Game &)>> ComponentFactory::_basicBuilders{
		{"Movable",          [](Game &    ){ return new Components::MovableComponent(); }},
		{"Position",         [](Game &    ){ return new Components::PositionComponent({0, 0}); }},
		{"Controllable",     [](Game &game){ return new Components::ControllableComponent(*game.state.settings.input, 2, 4); }},
		{"Displayable",      [](Game &game){ return new Components::DisplayableComponent(game.resources, "assets/entities/test.json"); }},
		{"BlockedByTerrain", [](Game &game){ return new Components::BlockedByTerrainComponent(game.state.map); }},
		{"Mana",             [](Game &    ){ return new Components::ManaComponent(20); }},
		{"Health",           [](Game &    ){ return new Components::HealthComponent(20); }},
		{"Name",             [](Game &    ){ return new Components::NameComponent(""); }},
		{"PlayerHUD",        [](Game &game){ return new Components::PlayerHUDComponent(game.state.hud); }},
		{"Inventory",        [](Game &    ){ return new Components::InventoryComponent(16); }},
		{"Interact",         [](Game &    ){ return new Components::InteractComponent(); }},
		{"Collision",        [](Game &    ){ return new Components::CollisionComponent({}); }},
		{"Collider",         [](Game &    ){ return new Components::ColliderComponent({}); }},
		{"Dialog",           [](Game &    ){ return new Components::DialogComponent(); }},
		{"Experience",       [](Game &    ){ return new Components::ExperienceComponent(); }},
		{"Deck",             [](Game &    ){ return new Components::DeckComponent("assets/spell_cards/test/test_tree.json"); }},
		{"Shoot",            [](Game &game){ return new Components::ShootComponent(game); }},
		{"OOBDie",           [](Game &game){ return new Components::OOBDieComponent(game.state.map); }},
		{"AI",               [](Game &game){ return new Components::AIComponent("assets/ais/allyDodge", 2, 4, game.state.map, game.state.map.getECSCore()); }},
		{"Cutscene",         [](Game &game){ return new Components::CutsceneComponent(game, "assets/cutscenes/testCutscene"); }},
		{"BossHUD",          [](Game &game){ return new Components::BossHUDComponent(game.state.hud); }},
		{"Projectile",       [](Game &game){ return new Components::ProjectileComponent(game, "assets/projectiles/testProjectile"); }}
	};

	Component *ComponentFactory::build(Game &game, const std::string &name, std::istream &stream)
	{
		try {
			return _builders.at(name)(game, stream);
		} catch (std::out_of_range &) {
			throw NoSuchComponentException("Cannot find any way to build a " + name + "Component");
		}
	}

	Component *ComponentFactory::build(TouhouFanGame::Game &game, const std::string &name)
	{
		try {
			return _basicBuilders.at(name)(game);
		} catch (std::out_of_range &) {
			throw NoSuchComponentException("Cannot find any way to build a " + name + "Component");
		}
	}

	std::vector<std::string> ComponentFactory::getItemList()
	{
		std::vector<std::string> list;

		list.reserve(_builders.size());
		for (auto &builder : _builders)
			list.push_back(builder.first);
		return list;
	}
}
