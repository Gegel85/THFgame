/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** ManaComponent.cpp
*/

#include <iostream>
#include "ManaComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	ManaComponent::ManaComponent(std::istream &stream) :
		Component("Mana")
	{
		stream >> this->mana >> this->maxMana;
	}

	ManaComponent::ManaComponent(float maxMana) :
		Component("Mana"),
		mana(maxMana),
		maxMana(maxMana)
	{}

	void ManaComponent::serialize(std::ostream &stream) const
	{
		stream << this->mana << " " << this->maxMana;
	}
}