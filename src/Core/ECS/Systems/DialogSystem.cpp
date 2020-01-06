//
// Created by Gegel85 on 06/01/2020.
//

#include "DialogSystem.hpp"
#include "../Components/InteractComponent.hpp"
#include "../Components/DialogComponent.hpp"
#include "../Components/PlayerHudComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	DialogSystem::DialogSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "Dialog", {"Interact"})
	{
	}

	void DialogSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &dialog = entity->getComponent("Dialog").to<Components::DialogComponent>();
		auto &interact = entity->getComponent("Interact").to<Components::InteractComponent>();

		if (
			interact.interactedWith &&
			interact.interactedWith->hasComponent("PlayerHUD") &&
			interact.interactedWith->hasComponent("Name")
		) {
			auto &hud = interact.interactedWith->getComponent("PlayerHUD").to<Components::PlayerHUDComponent>();

			hud.hud.setDialogManager(&dialog.manager);
			interact.interactedWith = nullptr;
		}
	}
}