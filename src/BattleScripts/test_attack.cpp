//
// Created by Gegel85 on 12/01/2020.
//

#include <vector>
#include "../Core/ECS/Entity.hpp"
#include "../Core/ECS/Components/PositionComponent.hpp"
#include "../Core/ECS/Components/MovableComponent.hpp"
#include "../Core/ECS/Components/DisplayableComponent.hpp"
#include "../Core/ECS/Core.hpp"
#include "../Core/ECS/Components/OobDieComponent.hpp"

unsigned int timer = 0;

TouhouFanGame::ECS::Entity *makeProjectile(TouhouFanGame::Map &map, TouhouFanGame::Resources &resources, sf::Vector2f pos, float dir)
{
	auto *p = new TouhouFanGame::ECS::Components::PositionComponent({12, 12});
	auto *m = new TouhouFanGame::ECS::Components::MovableComponent();
	auto *d = new TouhouFanGame::ECS::Components::DisplayableComponent(resources, "assets/entities/test.json");
	auto *o = new TouhouFanGame::ECS::Components::OOBDieComponent(map);

	p->position = pos;
	m->speed = 10;
	m->angleDir = dir;
	d->animation = TouhouFanGame::Rendering::ATTACKING;

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

		core.registerEntity(makeProjectile(map, resources, {pos.position.x + 8, pos.position.y + 8}, mov.angleDir));
	}
}