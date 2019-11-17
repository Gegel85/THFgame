//
// Created by Gegel85 on 26/09/2019.
//

#ifndef THFGAME_ENTITYFACTORY_HPP
#define THFGAME_ENTITYFACTORY_HPP


#include <string>
#include <map>
#include <functional>
#include "../Entity.hpp"

namespace TouhouFanGame
{
	struct Game;
	namespace ECS::Factory {
		//! @brief Builds Entity
		class EntityFactory {
		private:
			//! @brief Maps an Entity name to it's builder
			const static std::map<std::string, std::function<ECS::Entity *(Game &, unsigned int)>> _builders;

		public:
			//! @brief Builds an Entity and assign it an ID.
			//! @param name The name of the Entity to build.
			//! @param id The ID of the new Entity.
			//! @return The requested Entity.
			//! @throw NoSuchEntityException
			static Entity *build(Game &game, const std::string &name, unsigned int id);
		};
	}
}


#endif //THFGAME_ENTITYFACTORY_HPP
