//
// Created by Gegel85 on 26/01/2020.
//

#include <fstream>
#include "CardTree.hpp"
#include "ExternalCode/DynamicLibrary.hpp"

namespace TouhouFanGame
{
	Card::Card(const TouhouFanGame::Card &card) :
		neededLevel(card.neededLevel),
		name(card.name),
		texture(card.texture),
		description(card.description),
		handlerPath(card.handlerPath),
		handler(std::make_unique<DynamicLibrary>("assets/" + this->handlerPath + DLL_EXTENSION))
	{
	}

	Card::Card(nlohmann::json value) :
		neededLevel(value["level"]),
		name(value["name"]),
		texture(value["texture"]),
		description(value["description"]),
		handlerPath(value["handler"]),
		handler(std::make_unique<DynamicLibrary>("assets/" + this->handlerPath + DLL_EXTENSION))
	{
	}

	CardTree::CardTree(const std::string &filePath)
	{
		std::ifstream stream{filePath};
		nlohmann::json json;

		if (stream.fail())
			throw CorruptedCardTreeException(filePath + ": " + strerror(errno));

		try {
			stream >> json;
			stream.close();
			for (auto &val : json)
				this->_cards.emplace_back(val);
		} catch (std::exception &e) {
			stream.close();
			throw CorruptedCardTreeException(filePath + ": " + getLastExceptionName() + "\n" + e.what());
		}
	}

	const std::vector<Card> &CardTree::getUnlockedCards(unsigned int level)
	{
		this->_unlockedCards = std::vector<Card>(
			this->_cards.begin(),
			std::find_if(
				this->_cards.begin(),
				this->_cards.end(),
				[level](Card &card){
					return level < card.neededLevel;
				}
			)
		);

		return this->_unlockedCards;
	}
}