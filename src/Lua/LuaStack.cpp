//
// Created by Gegel85 on 17/03/2020.
//

#include "LuaStack.hpp"
#include "LuaState.hpp"

namespace TouhouFanGame::Lua
{
	LuaStack::LuaStack(LuaState &state) :
		_lua(state)
	{
	}

	std::shared_ptr<LuaValue> LuaStack::top() const
	{
		return LuaValue::make(this->_lua, -1);
	}
}