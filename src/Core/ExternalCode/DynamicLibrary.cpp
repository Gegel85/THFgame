/*
** EPITECH PROJECT, 2020
** THFgame
** File description:
** DynamicLibrary.cpp
*/

#include <dlfcn.h>
#include <cstring>
#include "DynamicLibrary.hpp"

namespace TouhouFanGame
{
	DynamicLibrary::DynamicLibrary(const std::string &path)
	{
		this->_handler = dlopen(path.c_str(), RTLD_LAZY);
		if (!this->_handler)
			throw InvalidDllException(path + ": " + strerror(errno));
	}

	DynamicLibrary::~DynamicLibrary()
	{
		dlclose(this->_handler);
	}

	void *DynamicLibrary::_call(const std::string &procName, std::vector<void *> args)
	{
		auto func = reinterpret_cast<void *(*)(std::vector<void *>)>(dlsym(this->_handler, procName.c_str()));

		if (!func)
			throw ProcedureNotFoundException("Cannot find procedure " + procName + " in this file.");
		return func(args);
	}
}