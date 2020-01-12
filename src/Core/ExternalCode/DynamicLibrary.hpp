/*
** EPITECH PROJECT, 2020
** THFgame
** File description:
** DynamicLibrary.hpp
*/

#ifndef THFGAME_DYNAMICLIBRARY_HPP
#define THFGAME_DYNAMICLIBRARY_HPP


#include "ExternalCode.hpp"
#ifndef _WIN32
typedef void * HMODULE;
#define DLL_EXTENSION ".so"
#else
#include <windows.h>
#define DLL_EXTENSION ".dll"
#endif

namespace TouhouFanGame
{
	class DynamicLibrary : public ExternalCode {
	private:
		HMODULE _handler;

		void *_call(const std::string &procName, std::vector<void *> args) override;

	public:
		void update() override;

		DynamicLibrary(const std::string &path);
		~DynamicLibrary();
	};
}


#endif //THFGAME_DYNAMICLIBRARY_HPP
