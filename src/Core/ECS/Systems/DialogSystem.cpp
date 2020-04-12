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
		auto &dialog = entity->getComponent(Dialog);
		auto &interact = entity->getComponent(Interact);

		if (dialog.triggered) {
			if (dialog.manager.finish()) {
				auto &hud = dialog.triggered->getComponent(PlayerHUD);

				dialog.manager.resetSprites();
				dialog.manager.setHolder(nullptr);
				hud.hud.setDialogManager(nullptr);
				try {
					dialog.triggered->getComponent(Controllable).disabled = false;
				} catch (NoSuchComponentException &) {}
				dialog.triggered = nullptr;
			}
			return;
		}

		if (interact.interactedWith.expired())
			return;

		auto interactedWith = interact.interactedWith.lock();

		if (
			interactedWith->hasComponent("PlayerHUD") &&
			interactedWith->hasComponent("Name")
		) {
			auto &hud = interactedWith->getComponent(PlayerHUD);

			dialog.triggered = interactedWith;
			dialog.manager.setHolder(entity);
			hud.hud.setDialogManager(&dialog.manager);
			try {
				interactedWith->getComponent(Controllable).disabled = true;
			} catch (NoSuchComponentException &) {}
			interact.interactedWith.reset();
		}
	}
}