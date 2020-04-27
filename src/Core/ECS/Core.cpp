//
// Created by Gegel85 on 27/09/2019.
//

#include <sstream>
#include "Core.hpp"
#include "Exceptions.hpp"
#include "Factories/EntityFactory.hpp"
#include "Factories/SystemFactory.hpp"
#include "../Resources/Game.hpp"

namespace TouhouFanGame::ECS
{
	Core::Core(Game &game) :
		_game(game)
	{
		Factory::SystemFactory::buildAll(*this, this->_systems);
	}

	std::weak_ptr<Entity> Core::makeEntity(const std::string &typeName)
	{
		try {
			while (true) this->getEntityByID(++this->_lastGivenID);
		} catch (NoSuchEntityException &) {}
		this->_entities.push_back(this->_factory.build(this->_game, typeName, this->_lastGivenID));

		auto entity = this->_entities.back();

		for (auto &comp : entity->getComponentsNames())
			this->_entitiesByComponent[comp].push_back(entity);
		return entity;
	}

	Game &Core::getGame()
	{
		return this->_game;
	}

	void Core::update()
	{
		std::for_each(this->_systems.begin(), this->_systems.end(), [](std::unique_ptr<System> &x){
			x->update();
		});

		auto entities = this->_entities;

		for (auto &entity : entities)
			for (auto &component : entity->getComponentsNames())
				try {
					System &system = this->getSystemByName(component);

					system.checkDependencies(*entity);
					system.updateEntity(entity);
				} catch (std::exception &e) {
					throw UpdateErrorException(
						"Error while updating entity #" + std::to_string(entity->getID()) +
						" (" + entity->getName() + ")\n"+
						component + "System :\n\t" +
						getLastExceptionName() + ": " + e.what()
					);
				}

		this->_entities.erase(
			std::remove_if(
				this->_entities.begin(),
				this->_entities.end(),
				[](std::shared_ptr<Entity> &ent) { return ent->toBeDestroyed(); }
			),
			this->_entities.end()
		);
		for (auto &vec : this->_entitiesByComponent)
			vec.second.erase(
				std::remove_if(
					vec.second.begin(),
					vec.second.end(),
					[](std::weak_ptr<Entity> &ent) { return ent.expired() || ent.lock()->toBeDestroyed(); }
				),
				vec.second.end()
			);
	}

	void Core::registerEntity(TouhouFanGame::ECS::Entity *entity)
	{
		this->registerEntity(std::shared_ptr<Entity>(entity));
	}

	void Core::deleteEntity(const std::shared_ptr<Entity> &entity)
	{
		for (size_t i = 0; i < this->_entities.size(); i++)
			if (this->_entities[i] == entity) {
				this->_entities.erase(this->_entities.begin() + i);
				for (auto &vec : this->_entitiesByComponent)
					vec.second.erase(
						std::remove_if(
							vec.second.begin(),
							vec.second.end(),
							[](std::weak_ptr<Entity> &ent) { return ent.expired(); }
						),
						vec.second.end()
					);
				return;
			}
	}

	void Core::deleteEntity(unsigned entityID)
	{
		this->deleteEntity(this->getEntityByID(entityID).lock());
	}

	void Core::clear(std::vector<unsigned int> whitelist)
	{
		this->_entitiesByComponent.clear();
		this->_lastGivenID = 0;
		if (whitelist.empty())
			return this->_entities.clear();
		for (size_t i = 0; i < this->_entities.size(); i++)
			if (std::find(whitelist.begin(), whitelist.end(), this->_entities[i]->getID()) == whitelist.end())
				this->_entities.erase(this->_entities.begin() + i--);
		for (auto &entity : this->_entities) {
			if (this->_lastGivenID < entity->getID())
				this->_lastGivenID = entity->getID();
			for (auto &comp : entity->getComponentsNames())
				this->_entitiesByComponent[comp].push_back(entity);
		}
	}

	System &Core::getSystemByName(const std::string &name) const
	{
		for (auto &system : this->_systems)
			if (system->getName() == name)
				return *system;
		throw NoSuchSystemException("Cannot find any System called \"" + name + "\"");
	}

	std::vector<std::weak_ptr<Entity>> Core::getEntityByName(const std::string &name)
	{
		std::vector<std::weak_ptr<Entity>> found;

		for (auto &entity : this->_entities)
			if (entity->getName() == name)
				found.push_back(entity);
		return found;
	}

	std::vector<std::weak_ptr<Entity>> Core::getEntityByComponent(const std::string &name)
	{
		try {
			return this->_entitiesByComponent.at(name);
		} catch (std::out_of_range &) {
			return {};
		}
	}

	std::weak_ptr<Entity> Core::registerEntity(std::shared_ptr<Entity> entity)
	{
		try {
			this->getEntityByID(entity->getID());
			try {
				while (true) this->getEntityByID(++this->_lastGivenID);
			} catch (NoSuchEntityException &) {}
			entity->_id = this->_lastGivenID;
		} catch (NoSuchEntityException &) {}
		for (auto &comp : entity->getComponentsNames())
			this->_entitiesByComponent[comp].push_back(entity);
		this->_entities.push_back(entity);
		return entity;
	}

	void Core::entityComponentChanged(const std::shared_ptr<Entity> &entity, const std::string &compName)
	{
		auto &array = this->_entitiesByComponent[compName];

		if (entity->hasComponent(compName)) {
			if (std::find_if(array.begin(), array.end(), [&entity](const std::weak_ptr<Entity> &ent){
				return ent.lock() == entity;
			}) == array.end())
				array.push_back(entity);
		} else {
			auto it = std::find_if(array.begin(), array.end(), [&entity](const std::weak_ptr<Entity> &ent){
				return ent.lock() == entity;
			});

			if (it != array.end())
				array.erase(it);
		}
	}

	std::weak_ptr<Entity> Core::getEntityByID(unsigned id) const
	{
		for (auto &entity : this->_entities)
			if (entity->getID() == id)
				return entity;
		throw NoSuchEntityException("Cannot find any entity with ID " + std::to_string(id));
	}

	void Core::serialize(std::ostream &stream) const
	{
		for (auto &entity : this->_entities)
			if (entity->isSerializable())
				stream << "Entity " << *entity << std::endl;
		stream << "THFG_ECS_Core_End";
	}

	void Core::unserialize(std::istream &stream)
	{
		std::string str;

		for (stream >> str; str != "THFG_ECS_Core_End" && !stream.eof(); stream >> str) {
			try {
				while (true) this->getEntityByID(++this->_lastGivenID);
			} catch (NoSuchEntityException &) {}

			auto entity = std::make_shared<Entity>(this->_lastGivenID);

			if (str != "Entity")
				throw InvalidSerializedString("Invalid Entity header");

			entity->unserialize(this->_game, stream);
			try {
				this->getEntityByID(entity->getID());
				throw InvalidSerializedString("Two entities have ID " + std::to_string(entity->getID()));
			} catch (NoSuchEntityException &) {
				for (auto &comp : entity->getComponentsNames())
					this->_entitiesByComponent[comp].push_back(entity);
				this->_entities.push_back(entity);
			}
		}

		if (str.empty())
			throw InvalidSerializedString("Unexpected EOF");
		if (str != "THFG_ECS_Core_End")
			throw InvalidSerializedString("Malformed footer (" + str + ")");
	}

	std::vector<std::weak_ptr<Entity>> Core::getEntities() const
	{
		std::vector<std::weak_ptr<Entity>> entities;

		std::for_each(this->_entities.begin(), this->_entities.end(), [&entities](const std::shared_ptr<Entity> &entity){
			entities.emplace_back(entity);
		});
		return entities;
	}

	const Factory::EntityFactory &Core::getFactory() const
	{
		return this->_factory;
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
