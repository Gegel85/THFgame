//
// Created by Gegel85 on 26/09/2019.
//

#include "Entity.hpp"
#include "Exceptions.hpp"

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

	void Entity::serialize(std::ostream &) const
	{
		if (!this->_serializable)
			return;
	}

	void Entity::unserialize(std::istream &)
	{}
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