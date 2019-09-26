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
		unsigned _id;
		std::string _name;
		std::vector<std::unique_ptr<Component>> _components;

	public:
		Entity(unsigned id, const std::string &name, const std::vector<Component *> &&components);
		unsigned getID();
		std::string getName();
		void update();
	};
}


#endif //THFGAME_ENTITY_HPP
