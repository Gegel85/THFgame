//
// Created by Gegel85 on 17/03/2020.
//

#ifndef THFGAME_LUANIL_HPP
#define THFGAME_LUANIL_HPP


#include "LuaValue.hpp"

namespace TouhouFanGame::Lua
{
	class LuaNil : public LuaValue {
	public:
		LuaNil() = default;

		std::string toString() const override;
		LuaType type() const override;
	};
}


#endif //THFGAME_LUANIL_HPP
