//
// Created by Gegel85 on 06/01/2020.
//

#include "DialogSystem.hpp"
#include "../Components/InteractComponent.hpp"
#include "../Components/DialogComponent.hpp"
#include "../Components/PlayerHudComponent.hpp"
#include "../Exceptions.hpp"
#include "../Components/ControllableComponent.hpp"

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

		if (dialog.triggered) {
			if (dialog.manager.finish()) {
				auto &hud = dialog.triggered->getComponent("PlayerHUD").to<Components::PlayerHUDComponent>();

				dialog.manager.resetSprites();
				dialog.manager.setHolder(nullptr);
				hud.hud.setDialogManager(nullptr);
				try {
					dialog.triggered->getComponent("Controllable").to<Components::ControllableComponent>().disabled = false;
				} catch (NoSuchComponentException &) {}
				dialog.triggered = nullptr;
			}
			return;
		}

		if (
			interact.interactedWith &&
			interact.interactedWith->hasComponent("PlayerHUD") &&
			interact.interactedWith->hasComponent("Name")
		) {
			auto &hud = interact.interactedWith->getComponent("PlayerHUD").to<Components::PlayerHUDComponent>();

			dialog.triggered = interact.interactedWith;
			dialog.manager.setHolder(entity);
			hud.hud.setDialogManager(&dialog.manager);
			try {
				interact.interactedWith->getComponent("Controllable").to<Components::ControllableComponent>().disabled = true;
			} catch (NoSuchComponentException &) {}
			interact.interactedWith = nullptr;
		}
	}
}