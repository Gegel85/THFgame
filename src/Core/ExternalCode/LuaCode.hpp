//
// Created by Gegel85 on 15/02/2020.
//

#ifndef THFGAME_LUACODE_HPP
#define THFGAME_LUACODE_HPP

#include "ExternalModule.hpp"

namespace TouhouFanGame
{
	class LuaCode : public ExternalModule {
	private:

	public:
		template<typename resultType, typename ...argsTypes>
		resultType call(const std::string &procName, argsTypes &...args) {
			//return this->_lua[procName].call<resultType>(args...);
		}

		LuaCode(const std::string &path);
		~LuaCode() override = default;
	};
}


#endif //THFGAME_LUACODE_HPP
