/*
** EPITECH PROJECT, 2020
** THFgame
** File description:
** ExternalCode.hpp
*/

#ifndef THFGAME_EXTERNALMODULE_HPP
#define THFGAME_EXTERNALMODULE_HPP


#include <functional>
#include <string>
#include <vector>
#include "../Exceptions.hpp"
#include "../Utils/BaseObject.hpp"

namespace TouhouFanGame
{
	class ExternalModule : public BaseObject {
	private:
		virtual void *_call(const std::string &procName, std::vector<std::reference_wrapper<BaseObject>> args) = 0;

	public:
		template<typename ...argsTypes>
		void call(const std::string &procName, argsTypes *...args)
		{
			try {
				this->call<int>(procName, args...);
			} catch (NullPointerException &) {}
		}

		template<typename returnType, typename ...argsTypes>
		returnType call(const std::string &procName, argsTypes *...args)
		{
			static_assert(sizeof(returnType) < sizeof(void *), "The size of the returned object must be less than size of a pointer");
			try {
				std::vector<BaseObject *> _args{args...};
				std::vector<std::reference_wrapper<BaseObject>> objs;

				objs.reserve(_args.size());
				for (size_t i = 0; i < _args.size(); i++) {
					if (!_args[i])
						throw InvalidArgumentsException("Argument " + std::to_string(i) + " to procedure " + procName + " was null, which is invalid.");
					objs.emplace_back(*_args[i]);
				}

				returnType *result = reinterpret_cast<returnType *>(this->_call(procName, objs));

				if (!result)
					throw NullPointerException();

				return *result;
			} catch (std::bad_cast &) {
				throw InvalidArgumentsException("An argument given to procedure '" + procName + "' had an invalid type.");
			} catch (std::exception &e) {
				throw ProcedureErrorException("An error occurred when running procedure '" + procName + "':\n" + getLastExceptionName() + ": " + e.what());
			}
		}

		virtual void update() = 0;

		virtual ~ExternalModule() override = default;
	};
}


#endif //THFGAME_EXTERNALMODULE_HPP
