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
#include "../../ExternalCode/ExternalModule.hpp"
#include "../../Resources/Resources.hpp"
#include "../../Resources/Map.hpp"

namespace TouhouFanGame::ECS::Components
{
	class ShootComponent : public ECS::Component {
	private:
		std::string _handlerPath;

	public:
		std::unique_ptr<ExternalModule> handler;
		bool shooting = false;
		Game &game;
		unsigned startCooldown;
		unsigned cooldown = 0;

		void setHandlerPath(const std::string &path);
		std::string getHandlerPath() const;

		//! @brief Unserializer constructor.
		ShootComponent(std::istream &stream, Game &game);
		ShootComponent(Game &game);
		ShootComponent(Game &game, const std::string &handlePath);
		~ShootComponent() override = default;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_SHOOTCOMPONENT_HPP
