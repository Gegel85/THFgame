/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** HealthComponent.hpp
*/

#ifndef THFGAME_HEALTHCOMPONENT_HPP
#define THFGAME_HEALTHCOMPONENT_HPP


#include "../Component.hpp"

namespace TouhouFanGame::ECS::Components
{
	//! @brief For Entity that have health bars.
	class HealthComponent : public Component {
	public:
		//! @brief The max health of this Entity.
		float maxHealth;

		//! @brief The current health of this Entity.
		float health;

		unsigned baseInvulnerability;

		//! @brief Invulnerability frames
		unsigned invulnerability;

		void takeDamages(unsigned damages);

		//! @brief Unserializer constructor.
		HealthComponent(std::istream &stream);
		HealthComponent(float maxHealth, unsigned baseInvulnerability);
		~HealthComponent() override = default;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_HEALTHCOMPONENT_HPP
