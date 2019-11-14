//
// Created by Gegel85 on 27/09/2019.
//

#ifndef THFGAME_CORE_HPP
#define THFGAME_CORE_HPP


#include <map>
#include <vector>
#include <memory>
#include "Entity.hpp"
#include "System.hpp"
#include "../Rendering/Screen.hpp"

namespace TouhouFanGame::ECS
{
	//! @brief The core of an ECS. It holds the System and Entity and make them interact with each other.
	class Core {
	private:
		//! @brief The last ID given to an Entity created.
		unsigned _lastGivenID = 0;

		//! @brief All the System loaded by the SystemFactory.
		std::vector<std::unique_ptr<System>> _systems;

		//! @brief All the Entity to be updated.
		std::vector<std::unique_ptr<Entity>> _entities;

		//! @brief Entities sorted by Component
		std::map<std::string, std::vector<std::reference_wrapper<Entity>>> _entitiesByComponent;

	public:
		Core();

		//! @brief Builds an Entity using the EntityFactory and keep it to be updated.
		//! @param typeName The name of the Entity to build. This will be given to the EntityFactory.
		//! @return The newly created Entity.
		//! @throw NoSuchEntityException If the Entity cannot be built.
		Entity &makeEntity(const std::string &typeName);

		//! @brief Get and Entity using it's ID.
		//! @param id The ID of the Entity to fetch.
		//! @return The Entity requested.
		//! @throw NoSuchEntityException
		Entity &getEntityByID(unsigned id) const;

		//! @brief Get all Entity with this name.
		//! @param name The name of the entities to return.
		//! @return A list of all the Entity matching this name.
		std::vector<std::reference_wrapper<Entity>> getEntityByName(const std::string &name);

		//! @brief Get all Entity containing this Component.
		//! @param name The name of the Component requested.
		//! @return A list of all the Entity matching this name.
		std::vector<std::reference_wrapper<Entity>> getEntityByComponent(const std::string &name);

		//! @brief Get a System by it's name.
		//! @param name The name of the Entity to fetch.
		//! @return The Entity requested.
		//! @throw NoSuchEntityException
		System &getSystemByName(const std::string &name) const;

		//! @brief Serialize to a stream.
		//! @param stream to load to.
		void serialize(std::ostream &stream) const;

		//! @brief Unserialize from a stream.
		//! @param stream to load from.
		void unserialize(std::istream &stream);

		//! @brief Updates all the Entity in the Core
		void update();

		//! @brief Deletes all the Entity in the Core besides the the Entity
		//! with an ID contained in the whitelist.
		//! @param whitelist A list of Entity's ID to leave in the Core.
		void clear(std::vector<unsigned int> whitelist = {});
	};
}

std::ostream	&operator<<(std::ostream &stream, const TouhouFanGame::ECS::Core &core);
std::istream	&operator>>(std::istream &stream, TouhouFanGame::ECS::Core &core);


#endif //THFGAME_CORE_HPP
