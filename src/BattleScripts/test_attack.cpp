//
// Created by Gegel85 on 12/01/2020.
//

#include <vector>
#include <iostream>
#include <cmath>
#include "../Core/ECS/Entity.hpp"
#include "../Core/ECS/Components/PositionComponent.hpp"
#include "../Core/ECS/Components/MovableComponent.hpp"
#include "../Core/ECS/Components/DisplayableComponent.hpp"
#include "../Core/ECS/Core.hpp"
#include "../Core/ECS/Components/OobDieComponent.hpp"
#include "../Core/DataType/Vector.hpp"

unsigned int timer = 0;

TouhouFanGame::ECS::Entity *makeProjectile(TouhouFanGame::Map &map, TouhouFanGame::Resources &resources, TouhouFanGame::Vector2f pos, double dir)
{
	auto *p = new TouhouFanGame::ECS::Components::PositionComponent({12, 12});
	auto *m = new TouhouFanGame::ECS::Components::MovableComponent();
	auto *d = new TouhouFanGame::ECS::Components::DisplayableComponent(resources, "assets/entities/test.json");
	auto *o = new TouhouFanGame::ECS::Components::OOBDieComponent(map);

	p->position = pos;
	m->speed = 10;
	m->angleDir = dir;
	p->angle = dir + M_PI_2;
	/*p->position = {
		static_cast<float>(map.getPixelSize().x),
		pos.y
	};
	m->speed = 10;
	m->angleDir = M_PI;
	d->spriteAngle = M_PI_2;
	d->animation = TouhouFanGame::Rendering::ATTACKING;*/

	return new TouhouFanGame::ECS::Entity(0, "PlayerProjectile", std::vector<TouhouFanGame::ECS::Component *>{
		m,
		d,
		p,
		o
	}, false);
}

extern "C"
{
	void update()
	{
		if (timer != 0)
			timer--;
	}

	void attackDefault(std::vector<void *> args)
	{
		if (timer != 0)
			return;

		if (args.size() != 4)
			throw std::bad_cast();

		timer = 10;

		auto &entity = *reinterpret_cast<std::shared_ptr<TouhouFanGame::ECS::Entity> *>(args[0]);
		auto &core = *reinterpret_cast<TouhouFanGame::ECS::Core *>(args[1]);
		auto &resources = *reinterpret_cast<TouhouFanGame::Resources *>(args[2]);
		auto &map = *reinterpret_cast<TouhouFanGame::Map *>(args[3]);
		auto &pos = entity->getComponent("Position").to<TouhouFanGame::ECS::Components::PositionComponent>();
		auto &mov = entity->getComponent("Movable").to<TouhouFanGame::ECS::Components::MovableComponent>();
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

		auto projectile1 = makeProjectile(map, resources, {
			static_cast<float>(pos.position.x + pos.size.x / 2 + vec.x * 6 - 6),
			static_cast<float>(pos.position.y + pos.size.y / 2 + vec.y * 6 - 6),
		}, angle);
		auto projectile2 = makeProjectile(map, resources, {
			static_cast<float>(pos.position.x + pos.size.x / 2 - vec.x * 6 - 6),
			static_cast<float>(pos.position.y + pos.size.y / 2 - vec.y * 6 - 6),
		}, angle);

		core.registerEntity(projectile1);
		core.registerEntity(projectile2);
	}
}