/*
** EPITECH PROJECT, 2020
** THFgame
** File description:
** ShootComponent.hpp
*/

#ifndef THFGAME_SHOOTCOMPONENT_HPP
#define THFGAME_SHOOTCOMPONENT_HPP


#include <string>
#include <memory>
#include "../Component.hpp"
#include "../../ExternalCode/ExternalCode.hpp"

namespace TouhouFanGame::ECS::Components
{
	//! @brief Given to Entity that exists somewhere
	class ShootComponent : public ECS::Component {
	private:
		//! @brief The name of the projectile created.
		std::string _handlerPath;

	public:
		std::unique_ptr<ExternalCode> handler;

		//! @brief Unserializer constructor.
		ShootComponent(std::istream &stream);
		ShootComponent(const std::string &handlePath);
		~ShootComponent() override = default;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_SHOOTCOMPONENT_HPP
