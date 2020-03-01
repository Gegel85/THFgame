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
	}

	DynamicLibrary::~DynamicLibrary()
	{
		dlclose(this->_handler);
	}
}