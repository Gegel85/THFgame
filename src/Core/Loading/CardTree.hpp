//
// Created by Gegel85 on 26/01/2020.
//

#ifndef THFGAME_CARDTREE_HPP
#define THFGAME_CARDTREE_HPP


#include <string>
#include <vector>
#include <memory>
#include <json.hpp>
#include "../ExternalCode/ExternalModule.hpp"

namespace TouhouFanGame
{
	struct Card : public BaseObject
	{
		unsigned neededLevel;
		unsigned manaCost;
		unsigned baseCooldown;
		unsigned cooldown = 0;
		std::string name;
		std::string texture;
		std::string description;
		std::string handlerPath;
		std::unique_ptr<ExternalModule> handler;

		Card(const Card &card);
		Card(nlohmann::json value);
		Card &operator=(const Card &);
		~Card() override = default;
	};

	class CardTree : public BaseObject {
	private:
		unsigned _lastLevelRequested = 0;
		std::vector<Card> _unlockedCards;
		std::vector<Card> _cards;

	public:
		CardTree(const std::string &filePath);
		~CardTree() override = default;

		void updateCards();
		Card &getCard(unsigned index);
		const std::vector<Card> &getCards() const;
		const std::vector<Card> &getUnlockedCards(unsigned level);
	};
}


#endif //THFGAME_CARDTREE_HPP
