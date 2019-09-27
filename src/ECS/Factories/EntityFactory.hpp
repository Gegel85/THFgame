//
// Created by Gegel85 on 26/09/2019.
//

#ifndef THFGAME_ENTITYFACTORY_HPP
#define THFGAME_ENTITYFACTORY_HPP


#include <string>
#include <map>
#include <functional>
#include "../Entity.hpp"

namespace TouhouFanGame::ECS::Factory
{
	class EntityFactory {
	private:
		static std::map<std::string, std::function<ECS::Entity *(unsigned int)>> _builders;

	public:
		static Entity *build(const std::string &name, unsigned int id);
	};
}


#endif //THFGAME_ENTITYFACTORY_HPP
