//
// Created by Gegel85 on 26/01/2020.
//

#include "DeckComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	DeckComponent::DeckComponent(const std::string &path) :
		Component("Deck"),
		_treePath(path),
		tree(path)
	{
	}
	
	DeckComponent::DeckComponent(std::istream &stream) :
		DeckComponent([&stream]{
			std::string str;

			stream >> str;
			return str;
		}())
	{
	}

	void DeckComponent::serialize(std::ostream &stream) const
	{
		stream << this->_treePath;
	}
}