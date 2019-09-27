//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_SYSTEMFACTORY_HPP
#define THFGAME_SYSTEMFACTORY_HPP


#include <vector>
#include <functional>
#include "../System.hpp"
#include "../Systems/DisplayableSystem.hpp"

namespace TouhouFanGame::ECS::Factory
{
	class SystemFactory {
	private:
		const static std::vector<std::function<System *(Core &)>> _builders;

	public:
		static void buildAll(Core &core, std::vector<std::unique_ptr<System>> &buffer);
	};
}


#endif //THFGAME_SYSTEMFACTORY_HPP
