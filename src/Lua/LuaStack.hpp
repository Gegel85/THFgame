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
		LuaState &_lua;

	public:
		LuaStack(LuaState &state);
		std::shared_ptr<LuaValue> top() const;
	};
}


#endif //THFGAME_LUASTACK_HPP
