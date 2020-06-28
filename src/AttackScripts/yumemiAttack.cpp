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
#define STAR_PROJ_SIZE TouhouFanGame::Vector2u{16, 16}

using Entity = TouhouFanGame::ECS::Entity;
using namespace TouhouFanGame::ECS::Components;

Entity *makeCrossProjectile(TouhouFanGame::Game &game, TouhouFanGame::Vector2f pos, const std::vector<std::string> &&targets = {"Player", "Ally"})
{
	auto *p = new PositionComponent({XSIZE, YSIZE});
	auto *m = new MovableComponent();
	auto *d = new DisplayableComponent(game.resources, "assets/entities/projectiles/crossProjectile.json");
	auto *proj = new ProjectileComponent(game, "assets/projectiles/yumemiCross", 10, LIFETIME, {}, static_cast<const std::vector<std::string> &&>(targets));
	auto *c = new CollisionComponent({
		new TouhouFanGame::ECS::Quadtree::RectangleCollider(0, 0, 0, 0, 0),
		new TouhouFanGame::ECS::Quadtree::RectangleCollider(0, 0, 0, 0, 0)
	});

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

Entity *makeStarProjectile(TouhouFanGame::ECS::Entity *me, TouhouFanGame::Game &game, TouhouFanGame::Vector2f pos, float angle, float speed, const std::vector<std::string> &&targets = {"Player", "Ally"})
{
	auto *p = new PositionComponent(STAR_PROJ_SIZE);
	auto *m = new MovableComponent();
	auto *d = new DisplayableComponent(game.resources, "assets/entities/projectiles/starProjectile.json");
	auto *proj = new ProjectileComponent(game, "assets/projectiles/testProjectile", 10, -1, me, static_cast<const std::vector<std::string> &&>(targets));
	auto *o = new OOBDieComponent(game.state.map);
	auto *c = new CollisionComponent({new TouhouFanGame::ECS::Quadtree::RectangleCollider(6, 6, 4, 4, 0)});

	p->position = pos;
	m->speed = speed;
	m->angleDir = angle;
	p->angle = angle + M_PI_2;
	d->animation = TouhouFanGame::Rendering::IDLE;

	return new TouhouFanGame::ECS::Entity(0, "BossProjectile", std::vector<TouhouFanGame::ECS::Component *>{
		m,
		d,
		p,
		c,
		o,
		proj
	}, false);
}

struct SolomonsBarrageState {
	int pos;
	int xOff;
	int yOff;
	int mapSizeX;
	int mapSizeY;
	unsigned part;
};

union SpellCardState {
	SolomonsBarrageState card0;
};

struct State {
	unsigned timer;
	TouhouFanGame::Game *game;
	TouhouFanGame::ECS::Core *core;
	TouhouFanGame::ECS::Entity *me;
	bool isCardActivated;
	unsigned cardActivated;
	SpellCardState state;
};

void handleSpellCard0Part0(State *state)
{
	bool finished = true;

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

		finished = false;
		state->core->registerEntity(
			makeCrossProjectile(
				*state->game,
				pos
			)
		);
	}

	state->timer = 13;
	state->state.card0.pos += 1;

	if (finished) {
		state->state.card0.part = 1;
		state->timer = 120;
		state->state.card0.pos = 0;
	}
}

void handleSpellCard0Part1(State *state)
{
	const auto &posCompM = state->me->getComponent(Position);
	const auto &posM = posCompM.position + posCompM.size / 2 - STAR_PROJ_SIZE / 2;
	const auto &posCompP = state->game->state.map.getPlayer()->getComponent(Position);
	const auto &posP = posCompP.position + posCompP.size / 2 - STAR_PROJ_SIZE / 2;
	double angle = posM.angle(posP);

	state->core->reserveNewSpace(8 * (state->state.card0.pos + 1));
	for (int j = 0; j < 8; j++) {
		float c = cos(angle);
		float s = sin(angle);

		for (int i = 0; i <= state->state.card0.pos; i++) {
			auto added = (i - state->state.card0.pos / 2.f) * 6;
			TouhouFanGame::Vector2f pos(posM.x, posM.y + added);
			TouhouFanGame::Vector2<float> rotatedPos{
				c * (pos.x - posM.x) - s * (pos.y - posM.y) + posM.x,
				s * (pos.x - posM.x) + c * (pos.y - posM.y) + posM.y
			};

			state->core->registerEntity(
				makeStarProjectile(
					state->me,
					*state->game,
					rotatedPos,
					angle,
					5
				)
			);
		}
		angle += M_PI_4;
	}

	state->game->resources.playSound("bullet_spawn");
	state->timer = 3;
	state->state.card0.pos += 1;

	if (state->state.card0.pos > 4) {
		state->state.card0.pos = 0;
		state->timer = 60;
		state->state.card0.part = state->game->resources.random() % 3 + 1;
	}
}

void handleSpellCard0Part2(State *state)
{
	const auto &posCompM = state->me->getComponent(Position);
	const auto &posM = posCompM.position + posCompM.size / 2 - STAR_PROJ_SIZE / 2;
	const auto &posCompP = state->game->state.map.getPlayer()->getComponent(Position);
	const auto &posP = posCompP.position + posCompP.size / 2 - STAR_PROJ_SIZE / 2;
	double angle = posM.angle(posP);

	state->game->resources.playSound("bullet_spawn");
	for (int i = 0; i < 90; i++) {
		state->core->registerEntity(
			makeStarProjectile(
				state->me,
				*state->game,
				posM,
				angle + (i * 4) * M_PI / 180,
				(i % 5 + 10) / 4.f
			)
		);
	}

	state->timer = 60;
	state->state.card0.part = state->game->resources.random() % 3 + 1;
}

void handleSpellCard0Part3(State *state)
{
	const auto &posCompM = state->me->getComponent(Position);
	const auto &posM = posCompM.position + posCompM.size / 2 - STAR_PROJ_SIZE / 2;

	if (!state->state.card0.pos)
		state->state.card0.pos = state->game->resources.random() % 20 + 5;

	state->game->resources.playSound("bullet_spawn");
	for (int i = 0; i < 30; i++) {
		state->core->registerEntity(
			makeStarProjectile(
				state->me,
				*state->game,
				posM,
				(i * 12) * M_PI / 180 + state->state.card0.pos % 2 * M_PI / 24,
				3
			)
		);
	}

	state->timer = 15;
	state->state.card0.pos--;

	if (!state->state.card0.pos) {
		state->state.card0.pos = 0;
		state->timer = 60;
		state->state.card0.part = state->game->resources.random() % 3 + 1;
	}
}

void handleSpellCard0(State *state)
{
	switch (state->state.card0.part) {
	case 0:
		return handleSpellCard0Part0(state);
	case 1:
		return handleSpellCard0Part1(state);
	case 2:
		return handleSpellCard0Part2(state);
	case 3:
		return handleSpellCard0Part3(state);
	default:
		state->isCardActivated = false;
		return;
	}
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

	unsigned spellCard0(State *state, Entity &me, TouhouFanGame::ECS::Core &core, TouhouFanGame::Game &game)
	{
		auto size = game.state.map.getPixelSize().to<int>();

		state->me = &me;
		state->game = &game;
		state->core = &core;
		state->cardActivated = 0;
		state->isCardActivated = true;
		state->state.card0.pos = 0;
		state->state.card0.part = 0;
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