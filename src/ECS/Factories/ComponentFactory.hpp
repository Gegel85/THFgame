/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** ComponentFactory.hpp
*/

#ifndef THFGAME_COMPONENTFACTORY_HPP
#define THFGAME_COMPONENTFACTORY_HPP


#include <functional>
#include <map>
#include "../Component.hpp"

namespace TouhouFanGame::ECS::Factory
{
	class ComponentFactory {
	private:
		//! @brief Maps a Component name to it's builder.
		static const std::map<std::string, std::function<Component *()>> _builders;

	public:
		//! @brief Builds an Entity and assign it an ID.
		//! @param name The name of the Entity to build.
		//! @return The requested Component.
		//! @throw NoSuchComponentException
		static Component *build(const std::string &name);
	};
}


#endif //THFGAME_COMPONENTFACTORY_HPP
