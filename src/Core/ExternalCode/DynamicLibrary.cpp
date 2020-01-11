/*
** EPITECH PROJECT, 2020
** THFgame
** File description:
** DynamicLibrary.cpp
*/

#ifndef _WIN32
#include <dlfcn.h>
#include <cstring>
#else
#include <windows.h>

#define dlopen(str, _) LoadLibraryA(str)
#define dlclose(handle) FreeLibrary(handle)
#define dlsym(handle, sym) reinterpret_cast<void *>(GetProcAddress(handle, sym))
#endif
#include "DynamicLibrary.hpp"

namespace TouhouFanGame
{
	std::string getError()
	{
#ifndef _WIN32
		return strerror(errno);
#else
		char *s = nullptr;

		FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			reinterpret_cast<LPSTR>(&s),
			0,
			NULL
		);

		return s;
#endif
	}

	DynamicLibrary::DynamicLibrary(const std::string &path)
	{
		this->_handler = dlopen(path.c_str(), 0);
		if (!this->_handler)
			throw InvalidDllException(path + ": " + getError());
	}

	DynamicLibrary::~DynamicLibrary()
	{
		dlclose(this->_handler);
	}

	void *DynamicLibrary::_call(const std::string &procName, std::vector<void *> args)
	{
		auto func = reinterpret_cast<void *(*)(std::vector<void *>)>(dlsym(this->_handler, procName.c_str()));

		if (!func)
			throw ProcedureNotFoundException("Error when trying to fetch " + procName + ": " + getError());
		return func(args);
	}
}