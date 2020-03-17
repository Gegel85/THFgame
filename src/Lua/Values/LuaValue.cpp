//
// Created by Gegel85 on 17/03/2020.
//

#include "LuaValue.hpp"
#include "LuaNoValue.hpp"
#include "LuaNil.hpp"
#include "LuaNumber.hpp"
#include "LuaString.hpp"

namespace TouhouFanGame::Lua
{
	std::shared_ptr<LuaValue> LuaValue::make(const std::shared_ptr<lua_State> &state, int index)
	{
		const char *cstr;
		size_t size;

		switch (lua_type(state.get(), index)) {
		case LUA_TNONE:
			return std::make_shared<LuaNoValue>();
		case LUA_TNIL:
			return std::make_shared<LuaNil>();
		case LUA_TNUMBER:
			return std::make_shared<LuaNumber>(lua_tonumber(state.get(), index));
		case LUA_TSTRING:
			cstr = lua_tolstring(state.get(), index, &size);
			return std::make_shared<LuaString>(std::string(cstr, size));
		default:
			return nullptr;
		}
	}

	std::shared_ptr<LuaValue> LuaValue::make(lua_Number value)
	{
		return std::make_shared<LuaNumber>(value);
	}

	std::shared_ptr<LuaValue> LuaValue::make(const std::string &value)
	{
		return std::shared_ptr<LuaValue>();
	}

	std::shared_ptr<LuaValue> LuaValue::make(const char *value)
	{
		return std::shared_ptr<LuaValue>();
	}
}