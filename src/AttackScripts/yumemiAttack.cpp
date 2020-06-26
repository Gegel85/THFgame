//
// Created by Gegel85 on 25/06/2020.
//

#include <vector>
#include <iostream>
#include <cmath>
#include "../Core/Resources/Game.hpp"
#include "../Core/Utils/BaseObject.hpp"
#include "../Core/ECS/Entity.hpp"
#include "../Core/Resources/Resources.hpp"
#include "../Core/ECS/Components/PositionComponent.hpp"
#include "../Core/ECS/Components/MovableComponent.hpp"
#include "../Core/ECS/Components/DisplayableComponent.hpp"
#include "../Core/ECS/Core.hpp"
#include "../Core/ECS/Components/OobDieComponent.hpp"
#include "../Core/ECS/Components/ColliderComponent.hpp"
#include "../Core/ECS/Quadtree/RectangleCollider.hpp"
#include "../Core/ECS/Components/ProjectileComponent.hpp"
#include "../Core/ECS/Components/CollisionComponent.hpp"

#define XSIZE 96
#define YSIZE 128
#define LIFETIME 2700

using Entity = TouhouFanGame::ECS::Entity;
using namespace TouhouFanGame::ECS::Components;

Entity *makeCrossProjectile(TouhouFanGame::Game &game, TouhouFanGame::Vector2f pos, const std::vector<std::string> &&targets = {"Player", "Ally"})
{
	auto *p = new PositionComponent({XSIZE, YSIZE});
	auto *m = new MovableComponent();
	auto *d = new DisplayableComponent(game.resources, "assets/entities/projectiles/crossProjectile.json");
	auto *proj = new ProjectileComponent(game, "assets/projectiles/yumemiCross", 10, LIFETIME, {}, static_cast<const std::vector<std::string> &&>(targets));
	//auto *c = new ColliderComponent(new TouhouFanGame::ECS::Quadtree::RectangleCollider(4, 4, 4, 4, 0)});
	auto *c = new CollisionComponent(new TouhouFanGame::ECS::Quadtree::RectangleCollider(0, 0, 0, 0, 0));

	p->position = pos;
	m->speed = 0;
	m->angleDir = 0;
	p->angle = 0;
	d->animation = TouhouFanGame::Rendering::IDLE;

	return new TouhouFanGame::ECS::Entity(0, "BossProjectile", std::vector<TouhouFanGame::ECS::Component *>{
		m,
		d,
		p,
		c,
		proj
	}, false);
}

struct SolomonsBarrageState {
	int pos;
	int xOff;
	int yOff;
	int mapSizeX;
	int mapSizeY;
};

union SpellCardState {
	SolomonsBarrageState card0;
};

struct State {
	unsigned timer;
	TouhouFanGame::Game *game;
	TouhouFanGame::ECS::Core *core;
	bool isCardActivated;
	unsigned cardActivated;
	SpellCardState state;
};

void handleSpellCard0(State *state)
{
	state->isCardActivated = false;
	for (int i = 0; i <= state->state.card0.pos; i++) {
		TouhouFanGame::Vector2f pos(
			state->state.card0.xOff + i * XSIZE,
			state->state.card0.yOff + (state->state.card0.pos - i) * YSIZE
		);

		if (
			pos.x >= state->state.card0.mapSizeX ||
			pos.y >= state->state.card0.mapSizeY
		)
			continue;

		state->isCardActivated = true;
		state->core->registerEntity(
			makeCrossProjectile(
				*state->game,
				pos
			)
		);
	}

	state->timer = 13;
	state->state.card0.pos += 1;
}

extern "C"
{
	State *makeUserData()
	{
		auto state = new State();

		return state;
	}

	void deleteUserData(State *data)
	{
		delete data;
	}

	void update(State *state)
	{
		if (state->timer) {
			state->timer--;
			return;
		}

		if (state->isCardActivated) {
			switch (state->cardActivated) {
			case 0:
				handleSpellCard0(state);
				break;
			default:
				break;
			}
		}
	}

	unsigned spellCard0(State *state, Entity &, TouhouFanGame::ECS::Core &core, TouhouFanGame::Game &game)
	{
		auto size = game.state.map.getPixelSize().to<int>();

		state->game = &game;
		state->core = &core;
		state->cardActivated = 0;
		state->isCardActivated = true;
		state->state.card0.pos = 0;
		state->state.card0.mapSizeX = size.x;
		state->state.card0.mapSizeY = size.y;
		state->state.card0.xOff = (XSIZE - (state->state.card0.mapSizeX % XSIZE)) % XSIZE / -2;
		state->state.card0.yOff = (YSIZE - (state->state.card0.mapSizeY % YSIZE)) % YSIZE / -2;
		return 0;
	}

	unsigned spellCard1(State *, TouhouFanGame::ECS::Entity &, TouhouFanGame::ECS::Core &, TouhouFanGame::Game &)
	{
		return 0;
	}

	unsigned spellCard2(State *, TouhouFanGame::ECS::Entity &, TouhouFanGame::ECS::Core &, TouhouFanGame::Game &)
	{
		return 0;
	}

	unsigned attackDefault(State *, TouhouFanGame::ECS::Entity &, TouhouFanGame::ECS::Core &, TouhouFanGame::Game &)
	{
		return 0;
	}
}