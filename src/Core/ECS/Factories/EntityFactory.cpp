//
// Created by Gegel85 on 26/09/2019.
//

#include <iostream>
#include "EntityFactory.hpp"
#include "../Exceptions.hpp"
#include "../Components/PositionComponent.hpp"
#include "../Components/DisplayableComponent.hpp"
#include "../Components/MovableComponent.hpp"
#include "../Components/ControllableComponent.hpp"
#include "../Components/BlockedByTerrainComponent.hpp"
#include "../../Game.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/ManaComponent.hpp"
#include "../Components/NameComponent.hpp"
#include "../Components/PlayerHudComponent.hpp"
#include "../Components/InventoryComponent.hpp"
#include "../Components/CollisionComponent.hpp"
#include "../Components/ShootComponent.hpp"

namespace TouhouFanGame::ECS::Factory
{
	EntityFactory::EntityFactory(const std::string &path)
	{
		std::ifstream stream{path};

		if (stream.fail())
			throw InvalidPrefabException(this->_builders.at(path) + ": " + strerror(errno));

		try {
			nlohmann::json j;

			stream >> j;
			this->_builders = j.get<std::map<std::string, std::string>>();
			stream.close();
		} catch (std::exception &e) {
			throw InvalidPrefabException(getLastExceptionName() + ":\n" + e.what());
		}
	}

	std::shared_ptr<Entity> EntityFactory::build(Game &game, const std::string &name, unsigned int id) const
	{
		if (name == "Entity")
			return std::make_shared<Entity>(id);

		try {
			std::ifstream stream{"assets/" + this->_builders.at(name)};

			if (stream.fail())
				throw InvalidPrefabException("assets/" + this->_builders.at(name) + ": " + strerror(errno));

			bool serializable;
			auto entity = std::make_shared<Entity>(id);

			entity->unserialize(game, stream);
			stream >> serializable;
			entity->setSerializable(serializable);
			stream.close();
			return entity;
		} catch (std::out_of_range &) {
			throw NoSuchEntityException("Cannot find any way to build a " + name);
		} catch (std::exception &e) {
			throw InvalidPrefabException(getLastExceptionName() + ":\n" + e.what());
		}
	}

	std::vector<std::string> EntityFactory::getItemList() const
	{
		std::vector<std::string> list{"Entity"};

		list.reserve(this->_builders.size() + 1);
		for (auto &builder : this->_builders)
			list.push_back(builder.first);
		return list;
	}
}