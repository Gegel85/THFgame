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
			//! @brief Maps an Entity name to it's builder file path
			std::map<std::string, std::string> _builders;

		public:
			//! @brief Builds the factory by giving it all prefabs.
			//! @param prefabsPath The path to the prefab json file.
			EntityFactory(const std::string &path);

			//! @brief Builds an Entity and assign it an ID.
			//! @param game Game resources and state.
			//! @param name The name of the Entity to build.
			//! @param id The ID of the new Entity.
			//! @return The requested Entity.
			//! @throw NoSuchEntityException
			std::shared_ptr<Entity> build(Game &game, const std::string &name, unsigned int id) const;

			//! @brief Returns a list of all the Entity this factory can build.
			std::vector<std::string> getItemList() const;
		};
	}
}


#endif //THFGAME_ENTITYFACTORY_HPP
