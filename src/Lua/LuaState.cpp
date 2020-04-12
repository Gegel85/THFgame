//
// Created by Gegel85 on 17/03/2020.
//

#include "LuaState.hpp"
#include "Exceptions.hpp"

namespace TouhouFanGame::Lua
{
	LuaState::LuaState() :
		_lua(luaL_newstate(), lua_close)
	{
	}

	LuaState::LuaState(lua_State *state) :
		_lua(state, lua_close)
	{
	}

	void LuaState::dofile(const std::string &path)
	{
		if (luaL_dofile(this->_lua.get(), path.c_str()))
			throw LuaRuntimeErrorException("Error running script " + path, *this);
	}

	void LuaState::dostring(const std::string &str)
	{
		if (luaL_dostring(this->_lua.get(), str.c_str()))
			throw LuaRuntimeErrorException("Error running script string", *this);
	}

	std::shared_ptr<lua_State> LuaState::state() const
	{
		return this->_lua;
	}

	LuaStack LuaState::stack()
	{
		return *this;
	}
}