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
		std::vector<Card> _unlockedCards;
		std::vector<Card> _cards;

	public:
		CardTree(const std::string &filePath);

		const std::vector<Card> &getUnlockedCards(unsigned level);
	};
}


#endif //THFGAME_CARDTREE_HPP
