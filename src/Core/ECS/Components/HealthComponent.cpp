/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** HealthComponent.cpp
*/

#include <iostream>
#include "HealthComponent.hpp"
#include "../Exceptions.hpp"

namespace TouhouFanGame::ECS::Components
{
	HealthComponent::HealthComponent(float maxHealth, unsigned baseInvulnerability) :
		Component("Health"),
		maxHealth(maxHealth),
		health(maxHealth),
		baseInvulnerability(baseInvulnerability),
		invulnerability(0)
	{}

	HealthComponent::HealthComponent(std::istream &stream) :
		Component("Health")
	{
		stream >> this->health >> this->maxHealth >> this->baseInvulnerability >> this->invulnerability;
		if (stream.fail())
			throw InvalidSerializedString("Invalid HealthComponent");
	}

	void HealthComponent::serialize(std::ostream &stream) const
	{
		stream << this->health << " " << this->maxHealth << " " << this->baseInvulnerability << " " << this->invulnerability;
	}

	void HealthComponent::takeDamages(unsigned int damages)
	{
		if (this->invulnerability)
			return;
		this->health -= damages;
		this->invulnerability = this->baseInvulnerability;
	}
}