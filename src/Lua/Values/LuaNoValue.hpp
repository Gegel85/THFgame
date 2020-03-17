//
// Created by Gegel85 on 17/03/2020.
//

#ifndef THFGAME_LUANOVALUE_HPP
#define THFGAME_LUANOVALUE_HPP


#include "LuaValue.hpp"

namespace TouhouFanGame::Lua
{
	class LuaNoValue : public LuaValue {
	public:
		LuaNoValue() = default;

		std::string toString() const override;

		LuaType type() const override;
	};
}


#endif //THFGAME_LUANOVALUE_HPP
