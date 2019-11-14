//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_SYSTEMFACTORY_HPP
#define THFGAME_SYSTEMFACTORY_HPP


#include <map>
#include <functional>
#include "../System.hpp"

namespace TouhouFanGame::ECS::Factory
{
	//! @brief Builds System
	class SystemFactory {
	private:
		//! @brief All the System that can be built.
		//TODO: Figure out why this doesn't work on MinGW
		const static std::vector<std::function<System *(Core &)>> _builders;

	public:
		//! @brief Builds one instance of each System.
		static void buildAll(Core &core, std::vector<std::unique_ptr<System>> &buffer);
	};
}


#endif //THFGAME_SYSTEMFACTORY_HPP
