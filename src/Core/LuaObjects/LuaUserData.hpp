//
// Created by Gegel85 on 15/02/2020.
//

#ifndef THFGAME_LUAUSERDATA_HPP
#define THFGAME_LUAUSERDATA_HPP


#include <vector>
#include <functional>
#include <sol.hpp>
#include "../Utils/BaseObject.hpp"

namespace TouhouFanGame::Lua
{
	class LuaUserData : public BaseObject {
	private:
		static const std::vector<std::function<void (sol::state &)>> _objInit;
		virtual void _init(sol::state &lua) = 0;

	public:
		~LuaUserData() override = default;

		static void init(sol::state &lua);
	};
}


#endif //THFGAME_LUAUSERDATA_HPP
