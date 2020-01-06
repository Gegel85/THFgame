/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** ManaSystem.hpp
*/

#ifndef THFGAME_MANASYSTEM_HPP
#define THFGAME_MANASYSTEM_HPP


#include "../System.hpp"

namespace TouhouFanGame::ECS::Systems
{
	//! @brief Updates Entity having a HealthComponent.
	class ManaSystem : public System {
	public:
		ManaSystem(Core &parent);
		void updateEntity(const std::shared_ptr<Entity> &entity) override;
	};
}


#endif //THFGAME_MANASYSTEM_HPP
