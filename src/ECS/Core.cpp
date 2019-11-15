//
// Created by Gegel85 on 27/09/2019.
//

#include <sstream>
#include "Core.hpp"
#include "Exceptions.hpp"
#include "Factories/EntityFactory.hpp"
#include "Factories/SystemFactory.hpp"
#include "../Game.hpp"

namespace TouhouFanGame::ECS
{
	Core::Core()
	{
		Factory::SystemFactory::buildAll(*this, this->_systems);
		logger.debug("Built " + std::to_string(this->_systems.size()) + " Systems");
		for (auto &system : this->_systems)
			logger.debug("Built " + system->getName() + "System");
	}

	Entity &Core::makeEntity(const std::string &typeName)
	{
		Entity &entity = *this->_entities.emplace_back(Factory::EntityFactory::build(typeName, this->_lastGivenID++));

		for (auto &comp : entity.getComponentsNames())
			this->_entitiesByComponent[comp].emplace_back(entity);
		return entity;
	}

	void Core::update()
	{
		for (auto &entity : this->_entities)
			for (auto &component : entity->getComponentsNames())
				try {
					System &system = this->getSystemByName(component);

					system.checkDependencies(*entity);
					system.updateEntity(*entity);
				} catch (std::exception &e) {
					throw UpdateErrorException(
						"Error while updating entity #" + std::to_string(entity->getID()) +
						" (" + entity->getName() + ")\n"+
						component + "System :\n\t" +
						getLastExceptionName() + ": " + e.what()
					);
				}
	}

	void Core::clear(std::vector<unsigned int> whitelist)
	{
		if (whitelist.empty())
			return this->_entities.clear();
		for (size_t i = 0; i < this->_entities.size(); i++)
			if (std::find(whitelist.begin(), whitelist.end(), this->_entities[i]->getID()) == whitelist.end())
				this->_entities.erase(this->_entities.begin() + i--);
		this->_entitiesByComponent.clear();
		for (auto &entity : this->_entities)
			for (auto &comp : entity->getComponentsNames())
				this->_entitiesByComponent[comp].emplace_back(*entity);
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
		try {
			return this->_entitiesByComponent.at(name);
		} catch (std::out_of_range &) {
			return {};
		}
	}

	Entity& Core::registerEntity(TouhouFanGame::ECS::Entity *entity)
	{
		try {
			this->getEntityByID(entity->getID());
			throw UpdateErrorException("An entity already have ID " + std::to_string(entity->getID()));
		} catch (NoSuchEntityException &) {
			return *this->_entities.emplace_back(entity);
		}
	}

	Entity &Core::getEntityByID(unsigned id) const
	{
		for (auto &entity : this->_entities)
			if (entity->getID() == id)
				return *entity;
		throw NoSuchEntityException("Cannot find any entity with ID " + std::to_string(id));
	}

	void Core::serialize(std::ostream &stream) const
	{
		for (auto &entity : this->_entities)
			if (entity->isSerializable())
				stream << "Entity " << *entity << std::endl;
		stream << "THFG_ECS_Core_End" << std::endl;
	}

	void Core::unserialize(std::istream &stream)
	{
		std::string str;

		for (stream >> str; str != "THFG_ECS_Core_End" && !stream.eof(); stream >> str) {
			Entity &entity = *this->_entities.emplace_back(new Entity());

			if (str != "Entity")
				throw InvalidSerializedString("Invalid Entity header");

			stream >> entity;
			if (&this->getEntityByID(entity.getID()) != &entity)
				throw InvalidSerializedString("Two entities have the same ID");
		}

		if (str != "THFG_ECS_Core_End")
			throw InvalidSerializedString("Unexpected EOF");
	}
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
