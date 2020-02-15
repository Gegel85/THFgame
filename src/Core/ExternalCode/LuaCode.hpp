//
// Created by Gegel85 on 15/02/2020.
//

#ifndef THFGAME_LUACODE_HPP
#define THFGAME_LUACODE_HPP


#include <sol.hpp>
#include "ExternalCode.hpp"

namespace TouhouFanGame
{
	class LuaCode : public ExternalCode {
	private:
		sol::state _lua;
		void *_call(const std::string &procName, std::vector<std::reference_wrapper<BaseObject>> args) override;

	public:
		void update() override;

		LuaCode(const std::string &path);
		~LuaCode() override;
	};
}


#endif //THFGAME_LUACODE_HPP
