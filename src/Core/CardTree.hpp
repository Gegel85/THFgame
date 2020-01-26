//
// Created by Gegel85 on 26/01/2020.
//

#ifndef THFGAME_CARDTREE_HPP
#define THFGAME_CARDTREE_HPP


#include <string>
#include <vector>
#include <memory>
#include <json.hpp>
#include "ExternalCode/ExternalCode.hpp"

namespace TouhouFanGame
{
	struct Card
	{
		unsigned neededLevel;
		unsigned manaCost;
		std::string name;
		std::string texture;
		std::string description;
		std::string handlerPath;
		std::unique_ptr<ExternalCode> handler;

		Card(const Card &card);
		Card(nlohmann::json value);
		Card &operator=(const Card &);
	};

	struct CardTree {
	private:
		unsigned _lastLevelRequested = 0;
		std::vector<Card> _unlockedCards;
		std::vector<Card> _cards;

	public:
		CardTree(const std::string &filePath);

		void updateCards();
		Card &getCard(unsigned index);
		const std::vector<Card> &getCards() const;
		const std::vector<Card> &getUnlockedCards(unsigned level);
	};
}


#endif //THFGAME_CARDTREE_HPP
