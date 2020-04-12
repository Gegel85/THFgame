//
// Created by Gegel85 on 17/03/2020.
//

#ifndef THFGAME_LUASTATE_HPP
#define THFGAME_LUASTATE_HPP

#include <string>
#include <lua.hpp>
#include <memory>
#include "LuaStack.hpp"

namespace TouhouFanGame::Lua
{
	class LuaState {
	private:
		std::shared_ptr<lua_State> _lua;

	public:
		LuaState();
		LuaState(std::nullptr_t) = delete;
		LuaState(lua_State *state);

		void dofile(const std::string &path);
		void dostring(const std::string &str);
		std::shared_ptr<lua_State> state() const;
		LuaStack stack();
	};
}


#endif //THFGAME_LUASTATE_HPP
