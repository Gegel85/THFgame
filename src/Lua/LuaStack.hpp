//
// Created by Gegel85 on 17/03/2020.
//

#ifndef THFGAME_LUASTACK_HPP
#define THFGAME_LUASTACK_HPP


#include <lua.hpp>
#include <memory>
#include "Values/LuaValue.hpp"

namespace TouhouFanGame::Lua
{
	class LuaStack {
	private:
		std::shared_ptr<lua_State> _lua;

	public:
		LuaStack(const std::shared_ptr<lua_State> &state);
		std::shared_ptr<LuaValue> top() const;
	};
}


#endif //THFGAME_LUASTACK_HPP
