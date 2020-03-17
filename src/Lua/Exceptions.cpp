//
// Created by Gegel85 on 17/03/2020.
//

#include "Exceptions.hpp"
#include "LuaState.hpp"

namespace TouhouFanGame::Lua
{
	LuaRuntimeErrorException::LuaRuntimeErrorException(const std::string &&msg, LuaState &state) :
		LuaException(static_cast<const std::string &&>(msg) + ": " + state.stack().top()->toString())
	{
	}

	LuaRuntimeErrorException::LuaRuntimeErrorException(const std::string &&msg) :
		LuaException(static_cast<const std::string &&>(msg))
	{
	}
}
