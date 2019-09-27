//
// Created by Gegel85 on 26/09/2019.
//

#ifndef THFGAME_EXCEPTIONS_HPP
#define THFGAME_EXCEPTIONS_HPP

#include <string>

namespace TouhouFanGame
{
	class BaseException : public std::exception {
	private:
		std::string _msg;

	public:
		explicit BaseException(const std::string &&msg) :
			_msg(msg)
		{};
		const char *what() const noexcept override {
			return this->_msg.c_str();
		};
	};

	class CorruptedAssetsListException : public BaseException {
	public:
		explicit CorruptedAssetsListException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	class CorruptedMapException : public BaseException {
	public:
		explicit CorruptedMapException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};
}

std::string getLastExceptionName();

#endif //THFGAME_EXCEPTIONS_HPP
