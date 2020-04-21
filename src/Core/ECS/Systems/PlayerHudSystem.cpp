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
		auto &health = entity->getComponent(Health);
		auto &mana = entity->getComponent(Mana);
		auto &name = entity->getComponent(Name);
		auto &hud = entity->getComponent(PlayerHUD);
		auto &exp = entity->getComponent(Experience);
		auto &deck = entity->getComponent(Deck);
		std::vector<std::string> textures;

		for (auto &card : deck.tree.getUnlockedCards(exp.level))
			textures.push_back(card.texture);
		hud.hud.setDispPlayerHUD(true);
		hud.hud.setPlayerName(name.name);
		hud.hud.setPlayerLife(health.health * 100 / health.maxHealth);
		hud.hud.setPlayerMana(mana.mana * 100 / mana.maxMana);
		hud.hud.setExpLevel(100 * exp.exp / exp.level / EXP_NEEDED);
		hud.hud.setCurrentLevel(exp.level);
		hud.hud.setSelectedCard(deck.selectedCard);
		hud.hud.setPlayerDeck(textures);
	}
}