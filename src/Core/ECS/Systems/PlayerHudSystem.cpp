//
// Created by Gegel85 on 18/11/2019.
//

#include "PlayerHudSystem.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/ManaComponent.hpp"
#include "../Components/PlayerHudComponent.hpp"
#include "../Components/NameComponent.hpp"
#include "../Components/ExperienceComponent.hpp"
#include "ExperienceSystem.hpp"
#include "../Components/DeckComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	PlayerHUDSystem::PlayerHUDSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "PlayerHUD", {"Name", "Mana", "Health", "Experience", "Deck"})
	{}

	void PlayerHUDSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &health = entity->getComponent("Health").to<Components::HealthComponent>();
		auto &mana = entity->getComponent("Mana").to<Components::ManaComponent>();
		auto &name = entity->getComponent("Name").to<Components::NameComponent>();
		auto &hud = entity->getComponent("PlayerHUD").to<Components::PlayerHUDComponent>();
		auto &exp = entity->getComponent("Experience").to<Components::ExperienceComponent>();
		auto &deck = entity->getComponent("Deck").to<Components::DeckComponent>();
		std::vector<std::string> textures;

		for (auto &card : deck.tree.getUnlockedCards(exp.level))
			textures.push_back(card.texture);
		hud.hud.setPlayerName(name.name);
		hud.hud.setPlayerLife(health.health * 100 / health.maxHealth);
		hud.hud.setPlayerMana(mana.mana * 100 / mana.maxMana);
		hud.hud.setExpLevel(100 * exp.exp / exp.level / EXP_NEEDED);
		hud.hud.setCurrentLevel(exp.level);
		hud.hud.setSelectedCard(deck.selectedCard);
		hud.hud.setPlayerDeck(textures);
	}
}