//
// Created by Gegel85 on 27/09/2019.
//

#ifndef THFGAME_RENDERING_EXCEPTION_HPP
#define THFGAME_RENDERING_EXCEPTION_HPP


#include "../Exceptions.hpp"

namespace TouhouFanGame::Rendering
{
	class InvalidAnimationConfigException : public BaseException {
	public:
		explicit InvalidAnimationConfigException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};
}


#endif //THFGAME_RENDERING_EXCEPTIONS_HPP
