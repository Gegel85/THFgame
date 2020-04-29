/*
** EPITECH PROJECT, 2020
** THFgame
** File description:
** DynamicLibrary.hpp
*/

#ifndef THFGAME_DYNAMICLIBRARY_HPP
#define THFGAME_DYNAMICLIBRARY_HPP


#include "ExternalModule.hpp"

#ifndef _WIN32
#include <dlfcn.h>
typedef void * HMODULE;
#define DLL_EXTENSION ".so"
#else
#include <windows.h>

#define RTLD_LAZY 0
#define dlopen(str, _) LoadLibraryA(str)
#define dlclose(handle) FreeLibrary(handle)
#define dlsym(handle, sym) reinterpret_cast<void *>(GetProcAddress(handle, sym))
#define DLL_EXTENSION ".dll"
#endif

namespace TouhouFanGame
{
	namespace Utils {
		std::string getLastError();
	}

	class DynamicLibrary : public ExternalModule {
	private:
		HMODULE _handler;
		void *_userdata = nullptr;

	public:
		template<typename resultType, typename ...argsTypes>
		resultType call(const std::string &procName, argsTypes &...args) {
			auto func = reinterpret_cast<resultType (*)(void *, argsTypes &...)>(dlsym(this->_handler, procName.c_str()));

			if (!func)
				throw ProcedureNotFoundException("Error when trying to fetch " + procName + ": " + Utils::getLastError());
			try {
				return func(this->_userdata, args...);
			} catch (std::exception &e) {
				throw ProcedureErrorException("An unhandled exception occurred in procedure \"" + procName + "\":\n" + getLastExceptionName() + ": " + e.what());
			}
		}

		DynamicLibrary(const std::string &path);
		~DynamicLibrary() override;
	};
}


#endif //THFGAME_DYNAMICLIBRARY_HPP
