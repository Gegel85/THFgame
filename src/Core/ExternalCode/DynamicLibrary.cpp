/*
** EPITECH PROJECT, 2020
** THFgame
** File description:
** DynamicLibrary.cpp
*/

#include "DynamicLibrary.hpp"

namespace TouhouFanGame
{
	DynamicLibrary::DynamicLibrary(const std::string &path)
	{
		this->_handler = dlopen(path.c_str(), RTLD_LAZY);
		if (!this->_handler)
			throw InvalidDllException(path + ": " + Utils::getLastError());

		auto func = reinterpret_cast<void *(*)()>(dlsym(this->_handler, "makeUserData"));

		if (func)
			this->_userdata = func();
	}

	DynamicLibrary::~DynamicLibrary()
	{
		auto func = reinterpret_cast<void (*)(void *)>(dlsym(this->_handler, "deleteUserData"));

		if (func)
			func(this->_userdata);

		dlclose(this->_handler);
	}
}