//
// Created by Gegel85 on 26/09/2019.
//

#ifndef THFGAME_EXCEPTIONS_HPP
#define THFGAME_EXCEPTIONS_HPP

#include <string>

namespace TouhouFanGame
{
	//! @brief The map is not loaded
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

	//! @brief The map is not loaded
	class CorruptedAssetsListException : public BaseException {
	public:
		explicit CorruptedAssetsListException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	//! @brief The map is corrupted
	class CorruptedMapException : public BaseException {
	public:
		explicit CorruptedMapException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	//! @brief The map is not loaded
	class MapNotLoadedException : public BaseException {
	public:
		explicit MapNotLoadedException() :
			BaseException("This map isn't loaded")
		{};
	};
}

std::string getLastExceptionName();

#endif //THFGAME_EXCEPTIONS_HPP
