//
// Created by Gegel85 on 27/09/2019.
//

#ifndef THFGAME_EXCEPTION_HPP
#define THFGAME_EXCEPTION_HPP


#include "../../Exceptions.hpp"

namespace TouhouFanGame::ECS
{
	//! @brief An error occurred when updating an entity.
	class UpdateErrorException : public BaseException {
	public:
		explicit UpdateErrorException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	//! @brief The System requested couldn't be found.
	class NoSuchSystemException : public BaseException {
	public:
		explicit NoSuchSystemException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	//! @brief A dependency required by a System was not satisfied.
	class MissingDependencyException : public BaseException {
	public:
		explicit MissingDependencyException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	//! @brief The Component requested couldn't be found on this Entity.
	class NoSuchComponentException : public BaseException {
	public:
		explicit NoSuchComponentException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	//! @brief The Entity requested couldn't be found.
	class NoSuchEntityException : public BaseException {
	public:
		explicit NoSuchEntityException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	//! @brief The serialized string is invalid.
	class InvalidSerializedString : public BaseException {
	public:
		explicit InvalidSerializedString(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	//! @brief Trying to serialize an object that is not serializable
	class NotSerializableException : public BaseException {
	public:
		explicit NotSerializableException() :
			BaseException("This object is not serializable")
		{};
	};
}


#endif //THFGAME_EXCEPTIONS_HPP
