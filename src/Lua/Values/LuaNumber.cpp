//
// Created by Gegel85 on 17/03/2020.
//

#include "LuaNumber.hpp"

namespace TouhouFanGame::Lua
{
	LuaNumber::LuaNumber(lua_Number value) :
		_value(value)
	{
	}

	std::string LuaNumber::toString() const
	{
		return std::to_string(this->_value);
	}

	LuaType LuaNumber::type() const
	{
		return LuaTypeNumber;
	}
}