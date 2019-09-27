//
// Created by Gegel85 on 27/09/2019.
//


#ifndef THFGAME_SYSTEM_HPP
#define THFGAME_SYSTEM_HPP


#include <string>
#include <vector>
#include "Entity.hpp"

namespace TouhouFanGame::ECS
{
	class Core;

	class System {
	private:
		std::string _name;
		std::vector<std::string> _deps;

	protected:
		Core &_core;

	public:
		System(Core &_parent, const std::string &&name, const std::vector<std::string> &&dependencies);
		void		checkDependencies(const Entity &);
		std::string	getName() const;
		virtual void	updateEntity(Entity &) = 0;
	};
}


#endif //THFGAME_SYSTEM_HPP
