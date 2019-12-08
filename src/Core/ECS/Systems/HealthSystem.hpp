/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** HealthSystem.hpp
*/

#ifndef THFGAME_HEALTHSYSTEM_HPP
#define THFGAME_HEALTHSYSTEM_HPP


#include "../System.hpp"

namespace TouhouFanGame::ECS::Systems
{
	//! @brief Updates Entity having a HealthComponent.
	class HealthSystem : public System {
	public:
		HealthSystem(Core &parent);
		void updateEntity(Entity &entity) override;
	};
}


#endif //THFGAME_HEALTHSYSTEM_HPP
