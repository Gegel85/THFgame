//
// Created by Gegel85 on 27/09/2019.
//

#include "Core.hpp"
#include "Exceptions.hpp"
#include "Factories/EntityFactory.hpp"
#include "Factories/SystemFactory.hpp"

namespace TouhouFanGame::ECS
{
	Core::Core()
	{
		Factory::SystemFactory::buildAll(*this, this->_systems);
	}

	Entity &Core::makeEntity(const std::string &typeName)
	{
		this->_entities.emplace_back(Factory::EntityFactory::build(typeName, this->_lastGivenID++));
		return *this->_entities.back();
	}

	void Core::update()
	{
		for (auto &entity : this->_entities)
			for (auto &component : entity->getComponentsNames())
				try {
					System &system = this->getSystemByName(component);

					system.checkDependencies(*entity);
					system.updateEntity(*entity);
				} catch (NoSuchSystemException &) {
				} catch (std::exception &e) {
					throw UpdateErrorException(
						"Error while updating entity n°" + std::to_string(entity->getID()) +
						"(" + entity->getName() + ")\n"+
						component + "System :\n\t" +
						getLastExceptionName() + ": " + e.what()
					);
				}
	}

	void Core::clear()
	{
		this->_entities.clear();
	}

	System &Core::getSystemByName(const std::string &name) const
	{
		for (auto &system : this->_systems)
			if (system->getName() == name)
				return *system;
		throw NoSuchSystemException("Cannot find any System called \"" + name + "\"");
	}

	std::vector<std::reference_wrapper<Entity>> Core::getEntityByName(const std::string &name)
	{
		std::vector<std::reference_wrapper<Entity>> found;

		for (auto &entity : this->_entities)
			if (entity->getName() == name)
				found.emplace_back(*entity);
		return found;
	}

	std::vector<std::reference_wrapper<Entity>> Core::getEntityByComponent(const std::string &name)
	{
		std::vector<std::reference_wrapper<Entity>> found;

		for (auto &entity : this->_entities)
			if (entity->hasComponent(name))
				found.emplace_back(*entity);
		return found;
	}

	Entity &Core::getEntityByID(unsigned id) const
	{
		for (auto &entity : this->_entities)
			if (entity->getID() == id)
				return *entity;
		throw NoSuchEntityException("Cannot find any entity with ID " + std::to_string(id));
	}

	void Core::serialize(std::ostream &stream) const
	{}

	void Core::unserialize(std::istream &stream)
	{}
}

std::ostream	&operator<<(std::ostream &stream, const TouhouFanGame::ECS::Core &core)
{
	core.serialize(stream);
	return stream;
}

std::istream	&operator>>(std::istream &stream, TouhouFanGame::ECS::Core &core)
{
	core.unserialize(stream);
	return stream;
}