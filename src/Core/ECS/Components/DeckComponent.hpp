//
// Created by Gegel85 on 26/01/2020.
//

#ifndef THFGAME_DECKCOMPONENT_HPP
#define THFGAME_DECKCOMPONENT_HPP


#include "../Component.hpp"
#include "../../Loading/CardTree.hpp"

namespace TouhouFanGame::ECS::Components
{
	//! @brief An entity that has a spell cards deck
	class DeckComponent : public Component {
	private:
		//! @brief The path to the card tree file.
		std::string _treePath;

	public:
		//! @brief The loaded card tree
		CardTree tree;

		//! @brief The currently selected card.
		unsigned selectedCard = 0;

		//! @brief Is the card currently being used.
		bool used = false;

		//! @brief Unserializer constructor.
		DeckComponent(std::istream &stream);
		DeckComponent(const std::string &path);
		~DeckComponent() override = default;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_DECKCOMPONENT_HPP
