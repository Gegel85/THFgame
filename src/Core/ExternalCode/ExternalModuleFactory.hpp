//
// Created by Gegel85 on 16/02/2020.
//

#ifndef THFGAME_EXTERNALMODULEFACTORY_HPP
#define THFGAME_EXTERNALMODULEFACTORY_HPP


#include <map>
#include "ExternalModule.hpp"

namespace TouhouFanGame
{
	class ExternalModuleFactory {
	private:
		static const std::map<std::string, std::function<ExternalModule *(const std::string &)>> _builders;

	public:
		//! @brief Builds a module.
		//! @note The builder will try to append the extensions to find which Module to build.
		static ExternalModule *build(const std::string &modulePath);
	};
}


#endif //THFGAME_EXTERNALMODULEFACTORY_HPP
