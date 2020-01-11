/*
** EPITECH PROJECT, 2020
** THFgame
** File description:
** ShootComponent.cpp
*/

#include <iostream>
#include "ShootComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	void ShootComponent::serialize(std::ostream &stream) const
	{
		stream << this->_handlerPath << '\0';
	}
}