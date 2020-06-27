//
// Created by Gegel85 on 25/06/2020.
//

#include <iostream>
#include <cstdint>
#include "../Core/Resources/Game.hpp"
#include "../Core/ECS/Quadtree/RectangleCollider.hpp"
#include "../Core/ECS/Components/ProjectileComponent.hpp"
#include "../Core/ECS/Components/DisplayableComponent.hpp"
#include "../Core/ECS/Components/HealthComponent.hpp"
#include "../Core/ECS/Components/CollisionComponent.hpp"

using Game = TouhouFanGame::Game;
using Entity = TouhouFanGame::ECS::Entity;
using RectangleCollider = TouhouFanGame::ECS::Quadtree::RectangleCollider;
using namespace TouhouFanGame::ECS::Components;

#define MAX_HEALTH (UINT32_MAX)
#define EXPAND_MILESTONE (80)
#define EXPAND_TIME (4)
#define STAY_MILESTONE (EXPAND_MILESTONE + EXPAND_TIME * 7)
#define RETRACT_MILESTONE(lifetime) (STAY_MILESTONE + lifetime)
#define DELETE_MILESTONE(lifetime) (RETRACT_MILESTONE(lifetime) + EXPAND_TIME * 7)

struct ProjectileState {
	Game *game;
	unsigned lifeTime;
};

const TouhouFanGame::Vector2f hitBoxes[][2][2] = {
	{{{40, 26}, {52, 58}},  {{30,34}, {62, 48}}},
	{{{40, 18}, {52, 66}},  {{22,34}, {70, 48}}},
	{{{40, 18}, {52, 80}},  {{20,34}, {72, 48}}},
	{{{40, 16}, {52, 86}},  {{16,34}, {76, 48}}},
	{{{40, 14}, {52, 96}},  {{14,34}, {80, 48}}},
	{{{40, 12}, {52, 104}}, {{12,34}, {82, 48}}},
	{{{40, 10}, {52, 112}}, {{10,34}, {84, 48}}},
	{{{40,  8}, {52, 118}}, {{ 8,34}, {86, 48}}}
};

void updateColliders(RectangleCollider &collider1, RectangleCollider &collider2, unsigned index)
{
	auto &elem = hitBoxes[index];

	collider1.setOffset(elem[0][0]);
	collider1.setSize(elem[0][1] - elem[0][0]);
	collider2.setOffset(elem[1][0]);
	collider2.setSize(elem[1][1] - elem[1][0]);
}

extern "C"
{
	ProjectileState *makeUserData()
	{
		auto *data = new ProjectileState{nullptr, 0};

		return data;
	}

	void deleteUserData(ProjectileState *data)
	{
		delete data;
	}

	void update(ProjectileState *data, ProjectileComponent &proj, Entity &me)
	{
		data->lifeTime++;
		if (data->lifeTime >= DELETE_MILESTONE(proj.lifeTime)) {
			me.destroy();
			return;
		}

		auto &disp = me.getComponent(Displayable);
		auto &collision = me.getComponent(Collision);
		auto *collider1 = reinterpret_cast<RectangleCollider *>(&*collision.colliders[0]);
		auto *collider2 = reinterpret_cast<RectangleCollider *>(&*collision.colliders[1]);

		if (data->lifeTime >= RETRACT_MILESTONE(proj.lifeTime)) {
			disp.animation = TouhouFanGame::Rendering::DEAD;
			updateColliders(*collider1, *collider2, 6 - (data->lifeTime - RETRACT_MILESTONE(proj.lifeTime)) / EXPAND_TIME);
		} else if (data->lifeTime >= STAY_MILESTONE) {
			disp.animation = TouhouFanGame::Rendering::WALK;
			updateColliders(*collider1, *collider2, 7);
		} else if (data->lifeTime >= EXPAND_MILESTONE) {
			disp.animation = TouhouFanGame::Rendering::RUN;
			updateColliders(*collider1, *collider2, std::max<int>((data->lifeTime - EXPAND_MILESTONE) / EXPAND_TIME - 1, 0));
		} else
			disp.animation = TouhouFanGame::Rendering::IDLE;
	}

	void onHit(ProjectileState *, ProjectileComponent &proj, Entity &, Entity &other, unsigned)
	{
		if (proj.owner == &other)
			return;

		if (other.hasComponent("Health"))
			other.getComponent(Health).takeDamages(proj.damages);
	}

	void onCreate(ProjectileState *data, ProjectileComponent &, Game &game)
	{
		data->game = &game;
	}

	void onDelete(ProjectileState *, ProjectileComponent &)
	{

	}

	void onLoad(ProjectileState *data, ProjectileComponent &, Game &game, std::istream &)
	{
		data->game = &game;
	}

	void onSave(ProjectileState *, ProjectileComponent &, std::ostream &)
	{

	}
}