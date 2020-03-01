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
	public:
		template<typename type>
		bool is()
		{
			return dynamic_cast<type *>(this);
		}

		template<typename type>
		type &to()
		{
			return dynamic_cast<type &>(*this);
		}

		virtual ~ExternalModule() override = default;
	};
}


#endif //THFGAME_EXTERNALMODULE_HPP
