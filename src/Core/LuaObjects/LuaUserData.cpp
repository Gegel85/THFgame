//
// Created by Gegel85 on 15/02/2020.
//

#include "LuaUserData.hpp"

namespace TouhouFanGame::Lua
{
	const std::vector<std::function<void (sol::state &)>> LuaUserData::_objInit{
	};

	void LuaUserData::init(sol::state &lua)
	{
		std::for_each(
			LuaUserData::_objInit.begin(),
			LuaUserData::_objInit.end(),
			[&lua](const std::function<void (sol::state &)> &fct){
				fct(lua);
			}
		);
	}
}