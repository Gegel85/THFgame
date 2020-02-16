/*
** EPITECH PROJECT, 2020
** THFgame
** File description:
** DynamicLibrary.cpp
*/

#ifndef _WIN32
#include <dlfcn.h>
#else
#include <windows.h>

#define RTLD_LAZY 0
#define dlopen(str, _) LoadLibraryA(str)
#define dlclose(handle) FreeLibrary(handle)
#define dlsym(handle, sym) reinterpret_cast<void *>(GetProcAddress(handle, sym))
#endif

#include "../Utils//BaseObject.hpp"
#include "DynamicLibrary.hpp"

namespace TouhouFanGame
{
	std::string getError()
	{
#ifndef _WIN32
		return dlerror();
#else
		char *s = nullptr;

		FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			reinterpret_cast<LPSTR>(&s),
			0,
			nullptr
		);

		return s;
#endif
	}

	DynamicLibrary::DynamicLibrary(const std::string &path)
	{
		this->_handler = dlopen(path.c_str(), RTLD_LAZY);
		if (!this->_handler)
			throw InvalidDllException(path + ": " + getError());
	}

	DynamicLibrary::~DynamicLibrary()
	{
		dlclose(this->_handler);
	}

	void *DynamicLibrary::_call(const std::string &procName, std::vector<std::reference_wrapper<BaseObject>> args)
	{
		static void *value;
		auto func = reinterpret_cast<void *(*)(std::vector<std::reference_wrapper<BaseObject>>)>(dlsym(this->_handler, procName.c_str()));

		if (!func)
			throw ProcedureNotFoundException("Error when trying to fetch " + procName + ": " + getError());
		value = func(args);
		return &value;
	}

	void DynamicLibrary::update()
	{
		auto func = reinterpret_cast<void (*)()>(dlsym(this->_handler, "update"));

		if (func)
			func();
	}
}