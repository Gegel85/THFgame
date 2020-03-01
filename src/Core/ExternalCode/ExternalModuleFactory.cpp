//
// Created by Gegel85 on 16/02/2020.
//

#include <filesystem>
#include "../Exceptions.hpp"
#include "ExternalModuleFactory.hpp"
#include "DynamicLibrary.hpp"
#include "LuaCode.hpp"
#include "../Resources/Game.hpp"

namespace TouhouFanGame
{
	const std::map<std::string, std::function<ExternalModule *(const std::string &)>> ExternalModuleFactory::_builders{
		{DLL_EXTENSION, [](const std::string &path){
			return new DynamicLibrary(path);
		}},
		{".lua", [](const std::string &path){
			return new LuaCode(path);
		}},
		{".luac", [](const std::string &path){
			return new LuaCode(path);
		}}
	};

	ExternalModule *ExternalModuleFactory::build(const std::string &modulePath)
	{
		for (auto &v : ExternalModuleFactory::_builders) {
			logger.debug("Checking " + modulePath + v.first);
			if (std::filesystem::exists(modulePath + v.first))
				return v.second(modulePath + v.first);
		}
		throw ModuleNotFoundException("There is no module called " + modulePath);
	}
}