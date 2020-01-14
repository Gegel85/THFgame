/*
** EPITECH PROJECT, 2020
** THFgame
** File description:
** OobDieSystem.hpp
*/

#ifndef THFGAME_OOBDIESYSTEM_HPP
#define THFGAME_OOBDIESYSTEM_HPP


#include "../System.hpp"

namespace TouhouFanGame::ECS::Systems
{
	//! @brief Updates Entity having a OOBDieComponent
	class OOBDieSystem : public System {
	public:
		OOBDieSystem(Core &core);
		void updateEntity(const std::shared_ptr<Entity> &) override;
	};
}


#endif //THFGAME_OOBDIESYSTEM_HPP
