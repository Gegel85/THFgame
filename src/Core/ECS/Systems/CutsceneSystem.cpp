//
// Created by Gegel85 on 16/04/2020.
//

#include "CutsceneSystem.hpp"
#include "../Components/CutsceneComponent.hpp"
#include "../../Utils/Utils.hpp"

namespace TouhouFanGame::ECS::Systems
{
	CutsceneSystem::CutsceneSystem(Core &core) :
		System(core, "Cutscene", {})
	{

	}

	void CutsceneSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &cut = entity->getComponent(Cutscene);

		if (cut.triggered)
			return;

		if (cut.isProgress)
			Utils::callExternalModule<void>(*cut.handler, "update");
		else if (Utils::callExternalModule<bool>(*cut.handler, "isConditionCompleted", *entity, cut.game)) {
			Utils::callExternalModule<void>(*cut.handler, "start", *entity, cut.game);
			cut.isProgress = true;
		}
		cut.handler;
	}
}