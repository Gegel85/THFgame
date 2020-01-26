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
		manaCost(card.manaCost),
		name(card.name),
		texture(card.texture),
		description(card.description),
		handlerPath(card.handlerPath),
		handler(std::make_unique<DynamicLibrary>("assets/" + this->handlerPath + DLL_EXTENSION))
	{
	}

	Card::Card(nlohmann::json value) :
		neededLevel(value["level"]),
		manaCost(value["cost"]),
		name(value["name"]),
		texture(value["texture"]),
		description(value["description"]),
		handlerPath(value["handler"]),
		handler(std::make_unique<DynamicLibrary>("assets/" + this->handlerPath + DLL_EXTENSION))
	{
	}

	Card &Card::operator=(const Card &card)
	{
		if (card.handlerPath != this->handlerPath)
			this->handler = std::make_unique<DynamicLibrary>("assets/" + card.handlerPath + DLL_EXTENSION);
		this->manaCost = card.manaCost;
		this->neededLevel = card.neededLevel;
		this->name = card.name;
		this->texture = card.texture;
		this->description = card.description;
		this->handlerPath = card.handlerPath;
		return *this;
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
		std::sort(this->_cards.begin(), this->_cards.end(), [](Card &c1, Card &c2){
			return c1.neededLevel < c2.neededLevel;
		});
	}

	Card &CardTree::getCard(unsigned index)
	{
		return this->_cards.at(index);
	}

	const std::vector<Card> & CardTree::getCards() const
	{
		return this->_cards;
	}

	const std::vector<Card> &CardTree::getUnlockedCards(unsigned int level)
	{
		if (this->_lastLevelRequested == level)
			return this->_unlockedCards;

		this->_lastLevelRequested = level;
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