//
// Created by Gegel85 on 26/09/2019.
//

#include <iostream>
#include "Entity.hpp"
#include "Exceptions.hpp"
#include "Factories/ComponentFactory.hpp"
#include "../Game.hpp"

namespace TouhouFanGame::ECS
{
	Entity::Entity(unsigned id, const std::string &name, const std::vector<Component *> &&components, bool serializable) :
		_serializable(serializable),
		_id(id),
		_name(name)
	{
		for (auto &component : components)
			this->_components.emplace_back(component);
	}

	std::string Entity::getName() const
	{
		return this->_name;
	}

	unsigned Entity::getID() const
	{
		return this->_id;
	}

	bool Entity::toBeDestroyed() const
	{
		return this->_toDel;
	}

	void Entity::destroy()
	{
		this->_toDel = true;
	}

	bool Entity::hasComponent(const std::string &name) const
	{
		try {
			this->getComponent(name);
		} catch (NoSuchComponentException &) {
			return false;
		}
		return true;
	}

	Component &Entity::getComponent(const std::string &name) const
	{
		for (auto &component : this->_components)
			if (component->getName() == name)
				return *component;
		throw NoSuchComponentException(
			"Cannot find any " + name +
			"Component in entity n°" + std::to_string(this->_id) +
			" (" + this->_name + ")"
		);
	}

	std::vector<std::string> Entity::getComponentsNames() const
	{
		std::vector<std::string> names;

		for (auto &component : this->_components)
			names.push_back(component->getName());

		return names;
	}

	bool Entity::isSerializable() const
	{
		return this->_serializable;
	}

	void Entity::serialize(std::ostream &stream) const
	{
		if (!this->_serializable)
			throw NotSerializableException();

		stream << this->_name << '\0' << this->_id << std::endl;
		for (auto &comp : this->_components)
			stream << comp->getName() << " " << *comp << std::endl;
		stream << "THFG_ECS_Entity_End";
	}

	void Entity::unserialize(std::istream &stream)
	{
		std::string str;

		logger.debug("Unserializing Entity");

		std::getline(stream, this->_name, '\0');
		while (!this->_name.empty() && std::isspace(this->_name[0]))
			this->_name.erase(this->_name.begin());

		if (this->_name.empty())
			throw InvalidSerializedString("The Entity name is empty");

		logger.debug("Name -> " + this->_name);

		stream >> this->_id;
		logger.debug("ID -> " + std::to_string(this->_id));

		for (stream >> str; str != "THFG_ECS_Entity_End" && !stream.eof(); stream >> str) {
			logger.debug("Unserialize component " + str);
			this->_components.emplace_back(Factory::ComponentFactory::build(str, stream));
		}

		if (str != "THFG_ECS_Entity_End")
			throw InvalidSerializedString("Unexpected EOF");
	}
}

std::ostream	&operator<<(std::ostream &stream, const TouhouFanGame::ECS::Entity &entity)
{
	entity.serialize(stream);
	return stream;
}

std::istream	&operator>>(std::istream &stream, TouhouFanGame::ECS::Entity &entity)
{
	entity.unserialize(stream);
	return stream;
}