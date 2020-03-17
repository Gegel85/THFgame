//
// Created by Gegel85 on 17/03/2020.
//

#include "LuaString.hpp"

namespace TouhouFanGame::Lua
{
	std::string LuaString::toString() const
	{
		return this->_value;
	}

	LuaType LuaString::type() const
	{
		return LuaTypeString;
	}

	LuaString::LuaString(const std::string &value) :
		_value(value)
	{
	}
}
