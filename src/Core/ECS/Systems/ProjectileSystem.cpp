//
// Created by Gegel85 on 29/04/2020.
//

#include "ProjectileSystem.hpp"
#include "../Components/ProjectileComponent.hpp"
#include "../Components/CollisionComponent.hpp"
#include "../../Utils/Utils.hpp"

namespace TouhouFanGame::ECS::Systems
{
	ProjectileSystem::ProjectileSystem(Core &core) :
		System(core, "Projectile", {"Collision"})
	{
	}

	void ProjectileSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &proj = entity->getComponent(Projectile);
		auto &col = entity->getComponent(Collision);

		for (auto &entry : col.collided)
			if (proj.targets.empty() || std::find(proj.targets.begin(), proj.targets.end(), entry.first->getName()) != proj.targets.end()) {
				Utils::callExternalModule<void>(*proj.effect, "onHit", proj, *entity, *entry.first, entry.second);
				if (entity->toBeDestroyed())
					break;
			}
		Utils::callExternalModule<void>(*proj.effect, "update", proj, *entity);
	}
}