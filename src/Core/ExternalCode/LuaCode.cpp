//
// Created by Gegel85 on 15/02/2020.
//

#include "LuaCode.hpp"
#include "../Exceptions.hpp"

namespace TouhouFanGame
{
	LuaCode::LuaCode(const std::string &path)
	{
		throw NotImplementedException("LuaCode::LuaCode(\"" + path + "\")");
	}

	void LuaCode::update()
	{
		throw NotImplementedException("LuaCode::update()");
	}

	void *LuaCode::_call(const std::string &procName, std::vector<std::reference_wrapper<BaseObject>> args)
	{
		throw NotImplementedException("LuaCode::_call(\"" + procName + "\", ...)");
	}
}