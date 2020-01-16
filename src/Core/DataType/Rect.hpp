//
// Created by anonymus-raccoon on 1/14/20.
//

#ifndef THFGAME_RECT_HPP
#define THFGAME_RECT_HPP

namespace TouhouFanGame {
	template<typename T>
	struct Rect {
		T x;
		T y;
		T w;
		T h;
	};

	typedef Rect<int> IntRect;
	typedef Rect<float> FloatRect;
}
#endif //THFGAME_RECT_HPP
