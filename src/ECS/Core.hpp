//
// Created by Gegel85 on 27/09/2019.
//

#ifndef THFGAME_CORE_HPP
#define THFGAME_CORE_HPP


#include <vector>
#include <memory>
#include "Entity.hpp"

namespace TouhouFanGame::ECS
{
	class Core {
	private:
		std::vector<std::unique_ptr<ECS::Entity>> _entities;

	public:
		Entity &getEntityByID(unsigned id);
		std::vector<Entity> getEntityByName(const std::string &name);
		std::vector<Entity> getEntityByComponent(const std::string &name);
		void update();
		void clear();
	};
}


#endif //THFGAME_CORE_HPP
