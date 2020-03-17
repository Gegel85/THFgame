//
// Created by Gegel85 on 17/03/2020.
//

#include "LuaStack.hpp"

namespace TouhouFanGame::Lua
{
	LuaStack::LuaStack(const std::shared_ptr<lua_State> &state) :
		_lua(state)
	{
	}

	std::shared_ptr<LuaValue> LuaStack::top() const
	{
		return LuaValue::make(this->_lua, -1);
	}
}