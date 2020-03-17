//
// Created by Gegel85 on 17/03/2020.
//

#ifndef THFGAME_EXCEPTIONS_HPP
#define THFGAME_EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace TouhouFanGame::Lua
{
	class LuaState;

	class LuaException : public std::exception {
	private:
		std::string _msg;

	public:
		explicit LuaException(const std::string &&msg) :
			_msg(msg)
		{};
		const char *what() const noexcept override {
			return this->_msg.c_str();
		};

		~LuaException() override = default;
	};

	class LuaRuntimeErrorException : public LuaException {
	public:
		LuaRuntimeErrorException(const std::string &&msg);
		LuaRuntimeErrorException(const std::string &&msg, LuaState &state);
	};
}

#endif //THFGAME_EXCEPTIONS_HPP
