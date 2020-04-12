//
// Created by Gegel85 on 17/03/2020.
//

#ifndef THFGAME_LUACONTAINER_HPP
#define THFGAME_LUACONTAINER_HPP


#include "Values/LuaValue.hpp"

namespace TouhouFanGame::Lua
{
	class LuaContainer {
	private:
		LuaState &_state;

	public:
		virtual LuaValue &operator[](const LuaValue &) = 0;

		LuaValue &operator[](const std::shared_ptr<LuaValue> &);
		LuaValue &operator[](lua_Number);
		LuaValue &operator[](const std::string &);
		LuaValue &operator[](const char *);
		LuaValue &operator[](bool);
	};
}


#endif //THFGAME_LUACONTAINER_HPP
