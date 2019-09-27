/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** Exception.hpp
*/

#ifndef THFGAME_EXCEPTION_HPP
#define THFGAME_EXCEPTION_HPP


#include "../Exceptions.hpp"

namespace TouhouFanGame::ECS
{
	class UpdateErrorException : public BaseException {
	public:
		explicit UpdateErrorException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	class NoSuchSystemException : public BaseException {
	public:
		explicit NoSuchSystemException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	class MissingDependencyException : public BaseException {
	public:
		explicit MissingDependencyException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	class NoSuchComponentException : public BaseException {
	public:
		explicit NoSuchComponentException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	class NoSuchEntityException : public BaseException {
	public:
		explicit NoSuchEntityException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};
}


#endif //THFGAME_EXCEPTIONS_HPP
