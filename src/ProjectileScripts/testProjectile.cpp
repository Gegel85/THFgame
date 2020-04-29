//
// Created by Gegel85 on 29/04/2020.
//

#include <iostream>
#include "../Core/ECS/Entity.hpp"
#include "../Core/ECS/Components/ProjectileComponent.hpp"

using Entity = TouhouFanGame::ECS::Entity;
using namespace TouhouFanGame::ECS::Components;

#define MAX_HEALTH 2

struct ProjectileState {
	std::vector<Entity *> entities;
};

extern "C"
{
	ProjectileState *makeUserData()
	{
		auto *data = new ProjectileState{{}};

		return data;
	}

	void deleteUserData(ProjectileState *data)
	{
		delete data;
	}

	void update(ProjectileState *, ProjectileComponent &, Entity &)
	{
	}

	void onHit(ProjectileState *data, ProjectileComponent &proj, Entity &me, Entity &other, unsigned layer)
	{
		if (&*proj.owner.lock() == &other)
			return;

		if (std::find(data->entities.begin(), data->entities.end(), &other) != data->entities.end())
			return;

		if (layer != 0)
			return;

		data->entities.push_back(&other);

		if (data->entities.size() == MAX_HEALTH)
			me.destroy();
	}

	void onCreate(ProjectileState *, ProjectileComponent &)
	{

	}

	void onDelete(ProjectileState *, ProjectileComponent &)
	{

	}

	void onLoad(ProjectileState *data, ProjectileComponent &, std::istream &stream)
	{
		unsigned len;

		stream >> len;
		data->entities.resize(len);
	}

	void onSave(ProjectileState *data, ProjectileComponent &, std::ostream &stream)
	{
		stream << data->entities.size();
	}
}