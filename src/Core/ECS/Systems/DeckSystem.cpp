//
// Created by Gegel85 on 26/01/2020.
//

#include "DeckSystem.hpp"
#include "../Components/DeckComponent.hpp"
#include "../Components/ExperienceComponent.hpp"
#include "../Components/ManaComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	DeckSystem::DeckSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "Deck", {"Experience", "Mana"})
	{
	}

	void DeckSystem::updateEntity(const std::shared_ptr<Entity> &entity)
	{
		auto &deck = entity->getComponent("Deck").to<Components::DeckComponent>();
		auto &mana = entity->getComponent("Mana").to<Components::ManaComponent>();
		auto &exp = entity->getComponent("Experience").to<Components::ExperienceComponent>();

		deck.selectedCard %= deck.tree.getUnlockedCards(exp.level).size();
		for (auto &card : deck.tree.getCards())
			card.handler->update();

		auto &card = deck.tree.getCard(deck.selectedCard);
		if (
			deck.used &&
			card.manaCost <= mana.mana &&
			card.handler->call<void>("spellCard" + std::to_string(deck.selectedCard))
		)
			mana.mana -= card.manaCost;
	}
}