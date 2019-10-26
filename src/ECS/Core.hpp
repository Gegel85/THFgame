//
// Created by Gegel85 on 27/09/2019.
//

#ifndef THFGAME_CORE_HPP
#define THFGAME_CORE_HPP


#include <map>
#include <vector>
#include <memory>
#include "Entity.hpp"
#include "System.hpp"
#include "../Rendering/Screen.hpp"

namespace TouhouFanGame::ECS
{
	class Core {
	private:
		unsigned _lastGivenID = 0;
		std::vector<std::unique_ptr<System>> _systems;
		std::vector<std::unique_ptr<Entity>> _entities;

	public:
		Core();
		Entity &makeEntity(const std::string &typeName);
		Entity &getEntityByID(unsigned id) const;
		std::vector<std::reference_wrapper<Entity>> getEntityByName(const std::string &name);
		std::vector<std::reference_wrapper<Entity>> getEntityByComponent(const std::string &name);
		System &getSystemByName(const std::string &name) const;
		void serialize(std::ostream &stream) const;
		void unserialize(std::istream &stream);
		void update();
		void clear(std::vector<unsigned int> whitelist = {});
	};
}

std::ostream	&operator<<(std::ostream &stream, const TouhouFanGame::ECS::Core &core);
std::istream	&operator>>(std::istream &stream, TouhouFanGame::ECS::Core &core);


#endif //THFGAME_CORE_HPP
