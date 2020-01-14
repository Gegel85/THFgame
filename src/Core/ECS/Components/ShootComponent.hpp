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
#include "../../Map.hpp"

namespace TouhouFanGame::ECS::Components
{
	class ShootComponent : public ECS::Component {
	private:
		std::string _handlerPath;

	public:
		std::unique_ptr<ExternalCode> handler;

		Map &map;

		bool shooting = false;

		Resources &resources;

		void setHandlerPath(const std::string &path);

		//! @brief Unserializer constructor.
		ShootComponent(std::istream &stream, Map &map, Resources &resources);
		ShootComponent(Resources &resources, Map &map);
		ShootComponent(Resources &resources, Map &map, const std::string &handlePath);
		~ShootComponent() override = default;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_SHOOTCOMPONENT_HPP
