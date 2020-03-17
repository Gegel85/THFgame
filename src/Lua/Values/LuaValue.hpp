//
// Created by Gegel85 on 17/03/2020.
//

#ifndef THFGAME_LUAVALUE_HPP
#define THFGAME_LUAVALUE_HPP

#include <string>
#include <memory>
#include <lua.hpp>
#include "LuaType.hpp"

namespace TouhouFanGame::Lua
{
	class LuaValue {
	public:
		virtual std::string toString() const = 0;
		virtual LuaType type() const = 0;

		static std::shared_ptr<LuaValue> make(const std::shared_ptr<lua_State>& state, int index = -1);
		static std::shared_ptr<LuaValue> make(int value);
		static std::shared_ptr<LuaValue> make(unsigned value);
		static std::shared_ptr<LuaValue> make(long value);
		static std::shared_ptr<LuaValue> make(unsigned long value);
		static std::shared_ptr<LuaValue> make(double value);
		static std::shared_ptr<LuaValue> make(float value);
		static std::shared_ptr<LuaValue> make(const std::string &value);
		static std::shared_ptr<LuaValue> make(const char *value);
	};
}

#endif //THFGAME_LUAVALUE_HPP
