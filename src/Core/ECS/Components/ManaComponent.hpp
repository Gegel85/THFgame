/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** ManaComponent.hpp
*/

#ifndef THFGAME_MANACOMPONENT_HPP
#define THFGAME_MANACOMPONENT_HPP


#include "../Component.hpp"

namespace TouhouFanGame::ECS::Components
{
	//! @brief For Entities that can have mana.
	class ManaComponent : public Component {
	public:
		//! @brief The current mana of this Entity.
		float mana;

		//! @brief The max mana of this Entity.
		float maxMana;

		//! @brief Unserializer constructor.
		ManaComponent(std::istream &stream);
		ManaComponent(float maxMana);
		~ManaComponent() override = default;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_MANACOMPONENT_HPP
