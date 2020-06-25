//
// Created by Gegel85 on 25/06/2020.
//

#include <iostream>
#include <cstdint>
#include "../Core/Resources/Game.hpp"
#include "../Core/ECS/Components/ProjectileComponent.hpp"
#include "../Core/ECS/Components/DisplayableComponent.hpp"
#include "../Core/ECS/Components/HealthComponent.hpp"

using Game = TouhouFanGame::Game;
using Entity = TouhouFanGame::ECS::Entity;
using namespace TouhouFanGame::ECS::Components;

#define MAX_HEALTH (UINT32_MAX)
#define EXPAND_MILESTONE (80)
#define STAY_MILESTONE (EXPAND_MILESTONE + 28)
#define RETRACT_MILESTONE(lifetime) (STAY_MILESTONE + lifetime)
#define DELETE_MILESTONE(lifetime) (RETRACT_MILESTONE(lifetime) + 28)

struct ProjectileState {
	std::vector<Entity *> entities;
	Game *game;
	unsigned lifeTime;
};

extern "C"
{
	ProjectileState *makeUserData()
	{
		auto *data = new ProjectileState{{}, nullptr, 0};

		return data;
	}

	void deleteUserData(ProjectileState *data)
	{
		delete data;
	}

	void update(ProjectileState *data, ProjectileComponent &proj, Entity &me)
	{
		data->lifeTime++;
		if (data->lifeTime > DELETE_MILESTONE(proj.lifeTime)) {
			me.destroy();
			return;
		}

		auto &disp = me.getComponent(Displayable);

		if (data->lifeTime >= RETRACT_MILESTONE(proj.lifeTime))
			disp.animation = TouhouFanGame::Rendering::DEAD;
		else if (data->lifeTime >= STAY_MILESTONE)
			disp.animation = TouhouFanGame::Rendering::WALK;
		else if (data->lifeTime >= EXPAND_MILESTONE)
			disp.animation = TouhouFanGame::Rendering::RUN;
		else
			disp.animation = TouhouFanGame::Rendering::IDLE;
	}

	void onHit(ProjectileState *data, ProjectileComponent &proj, Entity &, Entity &other, unsigned)
	{
		if (&*proj.owner.lock() == &other)
			return;

		if (std::find(data->entities.begin(), data->entities.end(), &other) != data->entities.end())
			return;

		if (other.hasComponent("Health"))
			other.getComponent(Health).health -= proj.damages;
	}

	void onCreate(ProjectileState *data, ProjectileComponent &, Game &game)
	{
		data->game = &game;
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