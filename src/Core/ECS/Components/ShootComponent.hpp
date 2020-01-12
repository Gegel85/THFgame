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
#include "../../Resources.hpp"

namespace TouhouFanGame::ECS::Components
{
	class ShootComponent : public ECS::Component {
	private:
		std::string _handlerPath;

	public:
		std::unique_ptr<ExternalCode> handler;

		bool shooting = false;

		Resources &resources;

		void setHandlerPath(const std::string &path);

		//! @brief Unserializer constructor.
		ShootComponent(std::istream &stream, Resources &resources);
		ShootComponent(Resources &resources);
		ShootComponent(Resources &resources, const std::string &handlePath);
		~ShootComponent() override = default;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_SHOOTCOMPONENT_HPP
