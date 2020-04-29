//
// Created by Gegel85 on 12/01/2020.
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

#define TIMER_SIZE 4

using Entity = TouhouFanGame::ECS::Entity;
using namespace TouhouFanGame::ECS::Components;

Entity *makeProjectile(TouhouFanGame::Game &game, TouhouFanGame::Vector2f pos, double dir, const std::vector<std::string> &&targets = {"Boss", "Enemy"})
{
	auto *p = new PositionComponent({12, 12});
	auto *m = new MovableComponent();
	auto *d = new DisplayableComponent(game.resources, "assets/entities/test.json");
	auto *proj = new ProjectileComponent(game, "assets/projectiles/testProjectile", 10, {}, static_cast<const std::vector<std::string> &&>(targets));
	auto *o = new OOBDieComponent(game.state.map);
	//auto *c = new ColliderComponent(new TouhouFanGame::ECS::Quadtree::RectangleCollider(4, 4, 4, 4, 0)});
	auto *c = new CollisionComponent(new TouhouFanGame::ECS::Quadtree::RectangleCollider(4, 4, 4, 4, 0));

	p->position = pos;
	m->speed = 10;
	m->angleDir = dir;
	p->angle = dir + M_PI_2;
	d->animation = TouhouFanGame::Rendering::ATTACKING;

	return new TouhouFanGame::ECS::Entity(0, "PlayerProjectile", std::vector<TouhouFanGame::ECS::Component *>{
		m,
		d,
		p,
		o,
		c,
		proj
	}, false);
}

extern "C"
{
	void update(void *)
	{
	}

	unsigned spellCard0(void *, Entity &entity, TouhouFanGame::ECS::Core &core, TouhouFanGame::Game &game)
	{
		auto &pos = entity.getComponent(Position);

		for (int i = 0; i < 16; i++) {
			auto angle = i * M_PI_4 / 2;

			core.registerEntity(makeProjectile(game, {
				static_cast<float>(pos.position.x + std::cos(angle) * 32 + pos.size.x / 2.),
				static_cast<float>(pos.position.y + std::sin(angle) * 32 + pos.size.y / 2.),
			}, angle));
		}
		return 0;
	}

	unsigned spellCard1(void *, TouhouFanGame::ECS::Entity &, TouhouFanGame::ECS::Core &core, TouhouFanGame::Game &game)
	{
		for (size_t i = 0; i < game.state.map.getPixelSize().y - 16; i += 4)
			core.registerEntity(makeProjectile(game, {
				static_cast<float>(game.state.map.getPixelSize().x - 16),
				static_cast<float>(i)
			}, M_PI, {"BossProjectiles"}));
		for (size_t i = 0; i < game.state.map.getPixelSize().y - 16; i += 4)
			core.registerEntity(makeProjectile(game, {
				0,
				static_cast<float>(i)
			}, 0, {"BossProjectiles"}));
		for (size_t i = 0; i < game.state.map.getPixelSize().x - 16; i += 4)
			core.registerEntity(makeProjectile(game, {
				static_cast<float>(i),
				0,
			}, M_PI_2, {"BossProjectiles"}));
		for (size_t i = 0; i < game.state.map.getPixelSize().x - 16; i += 4)
			core.registerEntity(makeProjectile(game, {
				static_cast<float>(i),
				static_cast<float>(game.state.map.getPixelSize().y - 16),
			}, -M_PI_2, {"BossProjectiles"}));
		return 0;
	}

	unsigned spellCard2(void *, TouhouFanGame::ECS::Entity &, TouhouFanGame::ECS::Core &core, TouhouFanGame::Game &game)
	{
		auto *p = new PositionComponent(game.state.map.getPixelSize());
		auto *m = new MovableComponent();
		auto *d = new DisplayableComponent(game.resources, "assets/entities/test.json");
		auto *o = new OOBDieComponent(game.state.map);
		auto *c = new CollisionComponent(new TouhouFanGame::ECS::Quadtree::RectangleCollider(0, 0, game.state.map.getPixelSize().x, game.state.map.getPixelSize().y, 0));
		auto *proj = new ProjectileComponent(game, "assets/projectiles/testProjectile", 60, {});

		p->position = {-static_cast<float>(p->size.x), 0};
		m->speed = 1;
		m->angleDir = 0;
		d->animation = TouhouFanGame::Rendering::ATTACKING;

		core.registerEntity(new TouhouFanGame::ECS::Entity(0, "PlayerProjectile", std::vector<TouhouFanGame::ECS::Component *>{
			m,
			d,
			p,
			o,
			c,
			proj
		}, false));
		return 0;
	}

	unsigned attackDefault(void *, TouhouFanGame::ECS::Entity &entity, TouhouFanGame::ECS::Core &core, TouhouFanGame::Game &game)
	{
		auto &pos = entity.getComponent(Position);
		auto &mov = entity.getComponent(Movable);
		auto angle = mov.angleDir;
		auto diff = std::fmod(mov.angleDir, M_PI_4);

		if (diff > M_PI_4 / 2)
			angle += M_PI_4 - diff;
		else
			angle -= diff;

		TouhouFanGame::Vector2<double> vec = {
			cos(angle + M_PI_2),
			sin(angle + M_PI_2),
		};

		core.registerEntity(makeProjectile(game, {
			static_cast<float>(pos.position.x + pos.size.x / 2 + vec.x * 6 - 6),
			static_cast<float>(pos.position.y + pos.size.y / 2 + vec.y * 6 - 6),
		}, angle));
		core.registerEntity(makeProjectile(game, {
			static_cast<float>(pos.position.x + pos.size.x / 2 - vec.x * 6 - 6),
			static_cast<float>(pos.position.y + pos.size.y / 2 - vec.y * 6 - 6),
		}, angle));
		return 0;
	}
}