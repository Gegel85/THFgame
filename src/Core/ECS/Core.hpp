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
#include "Factories/EntityFactory.hpp"

namespace TouhouFanGame
{
	struct Game;
}

namespace TouhouFanGame::ECS
{

	//! @brief The core of an ECS. It holds the System and Entity and make them interact with each other.
	class Core : public BaseObject {
	private:
		//! @brief The factory used to build entities
		Factory::EntityFactory _factory{"assets/entity_prefab.json"};

		//! @brief The Game this ECS is in.
		Game &_game;

		//! @brief The last ID given to an Entity created.
		unsigned _lastGivenID = 0;

		//! @brief All the System loaded by the SystemFactory.
		std::vector<std::unique_ptr<System>> _systems;

		//! @brief All the Entity to be updated.
		std::vector<std::shared_ptr<Entity>> _entities;

		//! @brief Entities sorted by Component
		std::map<std::string, std::vector<std::weak_ptr<Entity>>> _entitiesByComponent;

	public:
		Core(Game &game);

		~Core() override = default;

		//! @brief Builds an Entity using the EntityFactory and keep it to be updated.
		//! @param typeName The name of the Entity to build. This will be given to the EntityFactory.
		//! @return The newly created Entity.
		//! @throw NoSuchEntityException If the Entity cannot be built.
		std::weak_ptr<Entity> makeEntity(const std::string &typeName);

		//! @brief Registers an Entity in the Core. Will change the Entity ID if the ID is already taken.
		//! @param entity The Entity to register.
		//! @return The Entity registered.
		//! @warning NEVER USE THIS IN DYNAMIC MODULES (DLL, SO) !
		//! Also, avoid sharing shared_ptr with the core because you might have double free.
		//! If you are doing a projectile/shared library and want to register new entities that cannot
		//! be built by the EntityFactory, allocate the Entity using new and use the classic pointer version instead.
		std::weak_ptr<Entity> registerEntity(std::shared_ptr<Entity> entity);

		//! @brief Registers an Entity in the Core. Will change the Entity ID if the ID is already taken.
		//! @param entity The Entity to register.
		//! @note The Entity must have been built using new and will be deleted by the Core.
		std::weak_ptr<Entity> registerEntity(Entity *entity);

		//! @brief Get and Entity using it's ID.
		//! @param id The ID of the Entity to fetch.
		//! @return The Entity requested.
		//! @throw NoSuchEntityException
		std::weak_ptr<Entity> getEntityByID(unsigned id) const;

		//! @brief Get all Entity with this name.
		//! @param name The name of the entities to return.
		//! @return A list of all the Entity matching this name.
		std::vector<std::weak_ptr<Entity>> getEntityByName(const std::string &name);

		//! @brief Get all Entity containing this Component.
		//! @param name The name of the Component requested.
		//! @return A list of all the Entity matching this name.
		std::vector<std::weak_ptr<Entity>> getEntityByComponent(const std::string &name);

		//! @brief Get all Entity.
		//! @return A list of all the Entity created.
		std::vector<std::weak_ptr<Entity>> getEntities() const;

		//! @brief Get a System by it's name.
		//! @param name The name of the Entity to fetch.
		//! @return The System requested.
		//! @throw NoSuchEntityException
		System &getSystemByName(const std::string &name) const;

		//! @brief Serialize to a stream.
		//! @param stream to load to.
		void serialize(std::ostream &stream) const;

		//! @brief Unserialize from a stream.
		//! @param stream to load from.
		void unserialize(std::istream &stream);

		//! @brief Used to notify the Core that an Entity has More/less Component than before.
		//!        Therefore, it needs to update it's Component to Entity list.
		//! @param entity The entity that has its Component change.
		//! @param compName The name of the component added/deleted.
		void entityComponentChanged(const std::shared_ptr<Entity> &entity, const std::string &compName);

		//! @brief Updates all the Entity in the Core.
		void update();

		//! @brief Returns the Game object bound to this Core.
		Game &getGame();

		//! @brief Delete an Entity.
		void deleteEntity(const std::shared_ptr<Entity> &entity);

		//! @brief Delete an Entity.
		void deleteEntity(unsigned entityID);

		//! @brief Returns the factory this Core is using.
		const Factory::EntityFactory &getFactory() const;

		//! @brief Deletes all the Entity in the Core besides any Entity
		//! with an ID contained in the whitelist.
		//! @param whitelist A list of Entity's ID to leave in the Core.
		void clear(std::vector<unsigned int> whitelist = {});
	};
}

std::ostream	&operator<<(std::ostream &stream, const TouhouFanGame::ECS::Core &core);
std::istream	&operator>>(std::istream &stream, TouhouFanGame::ECS::Core &core);


#endif //THFGAME_CORE_HPP
