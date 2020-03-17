//
// Created by Gegel85 on 15/02/2020.
//

#include "LuaCode.hpp"
#include "../Exceptions.hpp"
//#include "../LuaObjects/LuaUserData.hpp"

namespace TouhouFanGame
{
	LuaCode::LuaCode(const std::string &path)
	{
		/*this->_lua.open_libraries(
			sol::lib::base,
			sol::lib::package,
			sol::lib::coroutine,
			sol::lib::string,
			sol::lib::table,
			sol::lib::math,
			sol::lib::io,
			sol::lib::os,
			sol::lib::debug,
			sol::lib::utf8
		);

		Lua::LuaUserData::init(this->_lua);*/
		this->_state.dofile(path);
	}
}