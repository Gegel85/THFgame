//
// Created by Gegel85 on 26/09/2019.
//

#ifndef THFGAME_ENTITY_HPP
#define THFGAME_ENTITY_HPP


#include <string>
#include <vector>
#include <memory>
#include "Component.hpp"

namespace TouhouFanGame::ECS
{
	//! @brief Entity containing Component and updated by System
	class Entity {
	private:
		//! @brief If this is the to false, the Entity will not be serialized.
		bool _serializable = true;

		//! @brief Whether this Entity is marked for deletion.
		bool _toDel = false;

		//! @brief The ID of the Entity.
		unsigned _id = 0;

		//! @brief The name of the Entity.
		std::string _name;

		//! @brief All the Components the Entity.
		std::vector<std::unique_ptr<Component>> _components;

	public:
		Entity() = default;

		//! @param id The ID of the Entity.
		//! @param name The name of the Entity.
		//! @param components The Component of the Entity.
		//! @param serializable Whether this Entity should be serialized or not.
		//! @warning The components contained in the components vector needs to be allocated using new.
		//! The will all be deleted when the Entity is destroyed.
		Entity(unsigned id, const std::string &name, const std::vector<Component *> &&components, bool serializable = true);

		//! @brief Fetch the ID of the Entity.
		//! @return The ID of this Entity.
		unsigned getID() const;

		//! @brief Fetch the name of the Entity.
		//! @return The name of this Entity.
		std::string getName() const;

		//! @brief Whether this Entity is marked for deletion.
		//! @return True has requested deletion. False otherwise.
		bool toBeDestroyed() const;

		//! @brief Whether the Entity can be serialized or not
		bool isSerializable() const;

		//! @brief Mark this Entity for deletion
		void destroy();

		//! @brief Whether this Entity has a "<name>Component".
		//! @return True if the requested Component was found. False otherwise.
		bool hasComponent(const std::string &name) const;

		//! @brief Returns the Component of the Entity that has this name.
		//! @return The requested Component.
		//! @throw ComponentNotFoundException
		Component &getComponent(const std::string &name) const;

		//! @brief Get all the Component's name this Entity has.
		//! @return A collection of Component names that this Entity has.
		std::vector<std::string> getComponentsNames() const;

		//! @brief Serializes an Entity to a stream.
		//! @throw NotSerializableException
		void serialize(std::ostream &) const;

		//! @brief Loads an Entity from a stream.
		void unserialize(std::istream &);
	};
}

std::ostream	&operator<<(std::ostream &stream, const TouhouFanGame::ECS::Entity &entity);
std::istream	&operator>>(std::istream &stream, TouhouFanGame::ECS::Entity &entity);


#endif //THFGAME_ENTITY_HPP
