/*
** EPITECH PROJECT, 2020
** THFgame
** File description:
** ExternalCode.hpp
*/

#ifndef THFGAME_EXTERNALCODE_HPP
#define THFGAME_EXTERNALCODE_HPP


#include <string>
#include <vector>
#include "../Exceptions.hpp"

namespace TouhouFanGame
{
	class ExternalCode {
	private:
		virtual void *_call(const std::string &procName, std::vector<void *> args) = 0;

	public:
		template<typename returnType, typename ...argsTypes>
		returnType *call(const std::string &procName, argsTypes *...args)
		{
			try {
				return dynamic_cast<returnType *>(this->_call(procName, {args...}));
			} catch (std::bad_cast &) {
				throw InvalidArgumentsException("An invalid argument was given to external procedure " + procName);
			}
		}

		virtual ~ExternalCode() = default;
	};
}


#endif //THFGAME_EXTERNALCODE_HPP
