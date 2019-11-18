/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** HealthComponent.cpp
*/

#include <iostream>
#include "HealthComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	HealthComponent::HealthComponent(float maxHealth) :
		Component("Health"),
		maxHealth(maxHealth),
		health(maxHealth)
	{}

	HealthComponent::HealthComponent(std::istream &stream) :
		Component("Health")
	{
		stream >> this->health >> this->maxHealth;
	}

	void HealthComponent::serialize(std::ostream &stream) const
	{
		stream << this->health << " " << this->maxHealth;
	}
}