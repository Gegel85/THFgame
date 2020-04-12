//
// Created by Gegel85 on 17/03/2020.
//

#include "LuaValue.hpp"
#include "LuaNoValue.hpp"
#include "LuaNil.hpp"
#include "LuaNumber.hpp"
#include "LuaString.hpp"
#include "../LuaState.hpp"

namespace TouhouFanGame::Lua
{
	std::shared_ptr<LuaValue> LuaValue::make(LuaState &state, int index)
	{
		const char *cstr;
		size_t size;

		switch (lua_type(&*state.state(), index)) {
		case LUA_TNONE:
			return std::make_shared<LuaNoValue>();
		case LUA_TNIL:
			return std::make_shared<LuaNil>();
		case LUA_TNUMBER:
			return std::make_shared<LuaNumber>(lua_tonumber(&*state.state(), index));
		case LUA_TSTRING:
			cstr = lua_tolstring(&*state.state(), index, &size);
			return std::make_shared<LuaString>(std::string(cstr, size));
		default:
			return nullptr;
		}
	}

	std::shared_ptr<LuaValue> LuaValue::make(lua_Number value)
	{
		return std::make_shared<LuaNumber>(value);
	}

	std::shared_ptr<LuaValue> LuaValue::make(int value)
	{
		return LuaValue::make(static_cast<lua_Number>(value));
	}

	std::shared_ptr<LuaValue> LuaValue::make(unsigned value)
	{
		return LuaValue::make(static_cast<lua_Number>(value));
	}

	std::shared_ptr<LuaValue> LuaValue::make(long value)
	{
		return LuaValue::make(static_cast<lua_Number>(value));
	}

	std::shared_ptr<LuaValue> LuaValue::make(unsigned long value)
	{
		return LuaValue::make(static_cast<lua_Number>(value));
	}

	std::shared_ptr<LuaValue> LuaValue::make(float value)
	{
		return LuaValue::make(static_cast<lua_Number>(value));
	}

	std::shared_ptr<LuaValue> LuaValue::make(const std::string &value)
	{
		return std::make_shared<LuaString>(value);
	}

	std::shared_ptr<LuaValue> LuaValue::make(const char *value)
	{
		return std::make_shared<LuaString>(value);
	}
}