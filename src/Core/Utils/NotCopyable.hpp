//
// Created by Gegel85 on 02/11/2019.
//

#ifndef THFGAME_NOTCOPYABLE_HPP
#define THFGAME_NOTCOPYABLE_HPP

namespace TouhouFanGame
{
	//! @brief A non copyable object
	class NotCopyable {
	public:
		NotCopyable(const NotCopyable &) = delete;
		NotCopyable &operator=(const NotCopyable &) = delete;
	};
}

#endif //THFGAME_NOTCOPYABLE_HPP
