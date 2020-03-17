//
// Created by Gegel85 on 17/03/2020.
//

#include "LuaNoValue.hpp"

namespace TouhouFanGame::Lua
{
	std::string LuaNoValue::toString() const
	{
		return "No value";
	}

	LuaType LuaNoValue::type() const
	{
		return LuaTypeNoValue;
	}
}
