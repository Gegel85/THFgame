//
// Created by Gegel85 on 15/02/2020.
//

#ifndef THFGAME_LUACODE_HPP
#define THFGAME_LUACODE_HPP


extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <sol.hpp>
#include "ExternalModule.hpp"

namespace TouhouFanGame
{
	class LuaCode : public ExternalModule {
	private:
		sol::state _lua;
		void *_call(const std::string &procName, std::vector<std::reference_wrapper<BaseObject>> args) override;

	public:
		void update() override;

		LuaCode(const std::string &path);
		~LuaCode() override = default;
	};
}


#endif //THFGAME_LUACODE_HPP
