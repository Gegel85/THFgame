//
// Created by Gegel85 on 22/04/2020.
//

#ifndef THFGAME_COLLIDERFACTORY_HPP
#define THFGAME_COLLIDERFACTORY_HPP


#include <string>
#include <map>
#include <functional>
#include "ICollider.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	class ColliderFactory {
	private:
		static const std::map<std::string, std::function<ICollider *()>> _builders;
		static const std::map<std::string, std::function<ICollider *(std::istream &stream)>> _unserializeBuilders;

	public:
		static ICollider *build(const std::string &name);
		static ICollider *build(const std::string &name, std::istream &stream);
	};
}


#endif //THFGAME_COLLIDERFACTORY_HPP
