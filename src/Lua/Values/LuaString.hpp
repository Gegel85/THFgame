//
// Created by Gegel85 on 17/03/2020.
//

#ifndef THFGAME_LUASTRING_HPP
#define THFGAME_LUASTRING_HPP


#include "LuaValue.hpp"

namespace TouhouFanGame::Lua
{
	class LuaString : public LuaValue {
	private:
		std::string _value;

	public:
		LuaString(const std::string &value);

		std::string toString() const override;
		LuaType type() const override;
	};
}


#endif //THFGAME_LUASTRING_HPP
