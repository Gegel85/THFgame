//
// Created by anonymus-raccoon on 1/14/20.
//

#ifndef THFGAME_RECT_HPP
#define THFGAME_RECT_HPP

#include "Vector.hpp"
#include "../Utils/BaseObject.hpp"

namespace TouhouFanGame {
	template<typename T>
	struct Rect : public BaseObject {
		Vector2<T> pt1;
		Vector2<T> pt2;
		Vector2<T> pt3;
		Vector2<T> pt4;

		template <typename T2>
		Rect(T x, T y, T2 w, T2 h, float angle)
			: pt1(x, y),
			pt2(x + w / std::cos(angle), y),
			pt3(x, y + h / std::cos(angle)),
			pt4(x + w / std::cos(angle), y + h / std::cos(angle))
		{}

		template <typename T2>
		Rect(Vector2<T> pos, Vector2<T2> size, float angle)
			: Rect(pos.x, pos.y, size.x, size.y, angle) {}

		~Rect() override = default;
	};

	typedef Rect<int> IntRect;
	typedef Rect<float> FloatRect;
}

template<typename T>
std::ostream &operator<<(std::ostream &s, const TouhouFanGame::Rect<T> &r)
{
	s << r.pt1.x << " "
	  << r.pt1.y << " "
	  << r.pt1.distance(r.pt2) << " "
	  << r.pt1.distance(r.pt3) << " "
	  << r.pt1.angle(r.pt2);
	return s;
}
#endif //THFGAME_RECT_HPP
