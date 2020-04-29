//
// Created by Gegel85 on 29/04/2020.
//

#include <iostream>
#include "../Core/Resources/Game.hpp"
#include "../Core/ECS/Entity.hpp"
#include "../Core/ECS/Components/ProjectileComponent.hpp"
#include "../Core/ECS/Components/HealthComponent.hpp"

using Game = TouhouFanGame::Game;
using Entity = TouhouFanGame::ECS::Entity;
using namespace TouhouFanGame::ECS::Components;

#define MAX_HEALTH 1

struct ProjectileState {
	std::vector<Entity *> entities;
	Game *game;
};

extern "C"
{
	ProjectileState *makeUserData()
	{
		auto *data = new ProjectileState{{}, nullptr};

		return data;
	}

	void deleteUserData(ProjectileState *data)
	{
		delete data;
	}

	void update(ProjectileState *, ProjectileComponent &, Entity &)
	{
	}

	void onHit(ProjectileState *data, ProjectileComponent &proj, Entity &me, Entity &other, unsigned)
	{
		if (&*proj.owner.lock() == &other)
			return;

		if (std::find(data->entities.begin(), data->entities.end(), &other) != data->entities.end())
			return;

		if (other.hasComponent("Health"))
			other.getComponent(Health).health -= proj.damages;

		data->entities.push_back(&other);

		if (data->entities.size() == MAX_HEALTH)
			me.destroy();
	}

	void onCreate(ProjectileState *data, ProjectileComponent &, Game &game)
	{
		data->game = &game;
		data->game->resources.playSound("bullet_spawn");
	}

	void onDelete(ProjectileState *, ProjectileComponent &)
	{

	}

	void onLoad(ProjectileState *data, ProjectileComponent &, Game &game, std::istream &stream)
	{
		unsigned len;

		stream >> len;
		data->entities.resize(len);
		data->game = &game;
	}

	void onSave(ProjectileState *data, ProjectileComponent &, std::ostream &stream)
	{
		stream << data->entities.size();
	}
}