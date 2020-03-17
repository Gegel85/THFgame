//
// Created by Gegel85 on 17/03/2020.
//

#ifndef THFGAME_LUANUMBER_HPP
#define THFGAME_LUANUMBER_HPP


#include "LuaValue.hpp"

namespace TouhouFanGame::Lua
{
	class LuaNumber : public LuaValue {
	private:
		lua_Number _value;

	public:
		LuaNumber(lua_Number value);

		std::string toString() const override;

		LuaType type() const override;
	};
}


#endif //THFGAME_LUANUMBER_HPP
