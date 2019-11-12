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
		static const std::map<std::string, std::function<Component *(std::istream &)>> _builders;

	public:
		//! @brief Builds a Component by unserializing it.
		//! @param name The name of the Entity to build.
		//! @param stream The stream to load from.
		//! @return The requested Component.
		//! @throw NoSuchComponentException
		static Component *build(const std::string &name, std::istream &stream);
	};
}


#endif //THFGAME_COMPONENTFACTORY_HPP
