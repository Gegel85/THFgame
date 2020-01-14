/*
** EPITECH PROJECT, 2020
** THFgame
** File description:
** OobDie.hpp
*/

#ifndef THFGAME_OOBDIECOMPONENT_HPP
#define THFGAME_OOBDIECOMPONENT_HPP


#include "../../Map.hpp"
#include "BasicSerializeComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	//! @brief An Entity destroyed when going out of bound.
	class OOBDieComponent : public BasicSerializeComponent {
	public:
		Map &map;

		OOBDieComponent(Map &map);
	};
}


#endif //THFGAME_OOBDIECOMPONENT_HPP
