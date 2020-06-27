//
// Created by Gegel85 on 27/06/2020.
//

#include <iostream>
#include "../Core/Resources/Game.hpp"
#include "../Core/ECS/Entity.hpp"
#include "../Core/ECS/Components/ProjectileComponent.hpp"
#include "../Core/ECS/Components/HealthComponent.hpp"
#include "../Core/ECS/Components/DisplayableComponent.hpp"

using Game = TouhouFanGame::Game;
using Entity = TouhouFanGame::ECS::Entity;
using namespace TouhouFanGame::ECS::Components;

struct ProjectileState {
	float angle;
};

extern "C"
{
	ProjectileState *makeUserData()
	{
		auto *data = new ProjectileState{0};

		return data;
	}

	void deleteUserData(ProjectileState *data)
	{
		delete data;
	}

	void update(ProjectileState *data, ProjectileComponent &, Entity &me)
	{
		auto &dis = me.getComponent(Displayable);

		dis.renderEntity.setSpriteAngle(data->angle += M_PI / 8);
	}

	void onHit(ProjectileState *, ProjectileComponent &proj, Entity &me, Entity &other, unsigned)
	{
		if (proj.owner == &other)
			return;

		if (other.hasComponent("Health"))
			other.getComponent(Health).takeDamages(proj.damages);

		me.destroy();
	}

	void onCreate(ProjectileState *, ProjectileComponent &, Game &)
	{

	}

	void onDelete(ProjectileState *, ProjectileComponent &)
	{

	}

	void onLoad(ProjectileState *, ProjectileComponent &, Game &, std::istream &)
	{
	}

	void onSave(ProjectileState *, ProjectileComponent &, std::ostream &)
	{
	}
}
