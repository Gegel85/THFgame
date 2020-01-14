/*
** EPITECH PROJECT, 2020
** THFgame
** File description:
** OobDie.cpp
*/

#include "OobDieComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	OOBDieComponent::OOBDieComponent(TouhouFanGame::Map &map) :
		BasicSerializeComponent("OOBDie"),
		map(map)
	{}
}