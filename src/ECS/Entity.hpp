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
	class Entity {
	private:
		bool _toDel = false;
		unsigned _id = 0;
		std::string _name;
		std::vector<std::unique_ptr<Component>> _components;

	public:
		Entity() = default;
		Entity(unsigned id, const std::string &name, const std::vector<Component *> &&components);
		unsigned getID() const;
		std::string getName() const;
		bool toBeDestroyed() const;
		void destroy();
		bool hasComponent(const std::string &name) const;
		Component &getComponent(const std::string &name) const;
		std::vector<std::string> getComponentsNames() const;
		void serialize(std::ostream &) const;
		void unserialize(std::istream &);
	};
}

std::ostream	&operator<<(std::ostream &stream, const TouhouFanGame::ECS::Entity &entity);
std::istream	&operator>>(std::istream &stream, TouhouFanGame::ECS::Entity &entity);


#endif //THFGAME_ENTITY_HPP
