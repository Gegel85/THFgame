//
// Created by Gegel85 on 26/09/2019.
//

#ifndef THFGAME_EXCEPTIONS_HPP
#define THFGAME_EXCEPTIONS_HPP

#include <string>

namespace TouhouFanGame
{
	//! @brief The base exception
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

	//! @brief The assets list is corrupted or invalid
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

	//! @brief The map couldn't be saved
	class MapSavingFailureException : public BaseException {
	public:
		explicit MapSavingFailureException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	//! @brief This file is not a valid saved map
	class InvalidSavedMap : public BaseException {
	public:
		explicit InvalidSavedMap(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	//! @brief The folder couldn't be created
	class FolderCreationErrorException : public BaseException {
	public:
		explicit FolderCreationErrorException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};
}

std::string getLastExceptionName();

#endif //THFGAME_EXCEPTIONS_HPP
