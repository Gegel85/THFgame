//
// Created by Gegel85 on 17/03/2020.
//

#include "LuaNil.hpp"

namespace TouhouFanGame::Lua
{
	std::string LuaNil::toString() const
	{
		return "nil";
	}

	LuaType LuaNil::type() const
	{
		return LuaTypeNil;
	}
}
