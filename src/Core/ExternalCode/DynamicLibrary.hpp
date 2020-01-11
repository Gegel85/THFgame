/*
** EPITECH PROJECT, 2020
** THFgame
** File description:
** DynamicLibrary.hpp
*/

#ifndef THFGAME_DYNAMICLIBRARY_HPP
#define THFGAME_DYNAMICLIBRARY_HPP


#include "ExternalCode.hpp"

namespace TouhouFanGame
{
	class DynamicLibrary : public ExternalCode {
	private:
		void *_handler;

		void *_call(const std::string &procName, std::vector<void *> args) override;

	public:
		DynamicLibrary(const std::string &path);
		~DynamicLibrary();
	};
}


#endif //THFGAME_DYNAMICLIBRARY_HPP
