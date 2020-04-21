//
// Created by Gegel85 on 26/01/2020.
//

#include "DeckSystem.hpp"
#include "../Components/DeckComponent.hpp"
#include "../Components/ExperienceComponent.hpp"
#include "../Components/ManaComponent.hpp"
#include "../Components/ShootComponent.hpp"
#include "../../Utils/Utils.hpp"

namespace TouhouFanGame::ECS::Systems
{
	DeckSystem::DeckSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "Deck", {"Experience", "Mana", "Shoot"})
	{
	}

	void DeckSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &deck = entity->getComponent(Deck);
		auto &mana = entity->getComponent(Mana);
		auto &exp = entity->getComponent(Experience);
		auto &shoot = entity->getComponent(Shoot);
		auto &cards = deck.tree.getUnlockedCards(exp.level);

		if (cards.empty())
			return;

		deck.selectedCard %= cards.size();
		deck.tree.updateCards();

		auto &card = deck.tree.getCard(deck.selectedCard);

		if (deck.used && card.manaCost <= mana.mana && !card.cooldown) {
			Utils::callExternalModule<void>(*card.handler, "spellCard" + std::to_string(deck.selectedCard), *entity, this->_core, shoot.resources, shoot.map);
			mana.mana -= card.manaCost;
			card.cooldown = card.baseCooldown;
		}
	}
}