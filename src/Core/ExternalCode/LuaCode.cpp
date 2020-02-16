//
// Created by Gegel85 on 15/02/2020.
//

#include "LuaCode.hpp"
#include "../Exceptions.hpp"

namespace TouhouFanGame
{
	LuaCode::LuaCode(const std::string &path)
	{
		this->_lua.open_libraries(
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

		this->_lua.script_file(path);
	}

	void LuaCode::update()
	{
		this->call("update");
	}

	void *LuaCode::_call(const std::string &procName, std::vector<std::reference_wrapper<BaseObject>> args)
	{
		throw NotImplementedException("LuaCode::_call(\"" + procName + "\", ...)");
	}
}